from pyspark.context import SparkContext
from pyspark.conf import SparkConf
from pyspark.streaming.context import StreamingContext
from pyspark.streaming.kafka import KafkaUtils
from pyspark.sql import Row, SparkSession, functions

from woody.common.config import Config
from py4j.protocol import Py4JJavaError
from datetime import datetime
from random import randint
import json 

def SparkSessionInstance(sparkConf):
    if ('sparkSessionSingletonInstance' not in globals()):
        globals()['sparkSessionSingletonInstance'] = SparkSession\
            .builder\
            .config(conf=sparkConf)\
            .getOrCreate()
    return globals()['sparkSessionSingletonInstance']


class ClickStreamAggr(object):
    """ClickStream aggregates
    """
    def __init__(self):
        conf = SparkConf()
        conf.set("spark.scheduler.mode", Config.spark_sched_mode)
        conf.set("spark.scheduler.pool", Config.spark_sched_pool)
        conf.set("spark.scheduler.allocation.file", Config.spark_sched_file)
        conf.set("spark.cassandra.auth.username", Config.cassandra_user)
        conf.set("spark.cassandra.auth.password", Config.cassandra_pass)

        self._sc = SparkContext(master=Config.spark_master, appName=self.__class__.__name__+str(randint(10,20)), conf=conf)
        self._sc.setLogLevel('WARN')
        self._ssc = StreamingContext(self._sc, Config.ssc_duration)
        self._sess = SparkSessionInstance(conf)
        self._keyspace = "woody_clickstream"
        self._from_kfk()

    def _from_kfk(self):
        # TODO: END_OF_STREAM EOFError
        kfk_params = {
            'metadata.broker.list': Config.kafka_brokers,
            'group.id': self.__class__.__name__,
            }
        self._click_ds = KafkaUtils.createDirectStream(self._ssc, ["click_ev"], kfk_params)
        self._buy_ds = KafkaUtils.createDirectStream(self._ssc, ["buy_ev"], kfk_params)
        """
        citi = self._sess.read.format("org.apache.spark.sql.cassandra")\
            .options(table="citizenship", keyspace=self._keyspace)\
            .load()
        citi.show()
        #dates.saveAsTextFiles(self.__class__.__name__)
        """
        # 2014-04-07T10:51:09.277Z
        fmt = "%Y-%m-%dT%H:%M:%S.%fZ"
        click = self._click_ds.map(lambda x: json.loads(x[1]))
        def click_conv(x):
            x['timestamp'] = datetime.strptime(x['timestamp'], fmt)
            return x

        click = click.map(click_conv)
        #click.count().pprint()
        click.foreachRDD(self.persist_click)

        self.aggr_session_click(click)
        self.aggr_item_click(click)

        buy = self._buy_ds.map(lambda x: json.loads(x[1]))

        def buy_conv(x):
            x['price'] = float(x['price'])
            x['quantity'] = int(x['quantity'])
            x['timestamp'] = datetime.strptime(x['timestamp'], fmt)
            return x
        buy = buy.map(buy_conv)
        buy.foreachRDD(self.persist_buy)
        
        # self.aggr_buy_click_delta(click, buy)
        self.aggr_session_quan(buy)
        self.aggr_item_quan(buy)

    def aggr_buy_click_delta(self, click, buy):
        """delta of buy timestamp and click timestamp
        TODO(zex): two test datasets doesn't come up in order of time
        """
        def earlist(x, y):
            if not x:
                return y
            if not y:
                return x
            if x < y: # timestamp
                return x
            return y

        def persist(time, rdd):
            if len(rdd.collect()) == 0:
                return

            columns = ("item_id", "price", "ts_click", "ts_buy", "session_id", "ts_delta")
            df, full_df = None, None

            try:
                rdd = rdd.map(lambda x: x[0].split('-') + [x[1][0][0],x[1][0][1]] + [x[1][1]])
                df = self._sess.createDataFrame(rdd, ["session_id", "item_id", "ts_click", "ts_buy", "price"])\
                        .dropDuplicates()
                full_df = df.dropna()
            except Exception as e:
                print("aggr_buy_click_delta transform failed", e)
            """
            price = self._sess.read.format("org.apache.spark.sql.cassandra")\
                .options(table="buy_event", keyspace=self._keyspace)\
                .load()
            """
            try:
                if full_df.count() > 0:
                    full_df = full_df.withColumn("ts_delta", full_df["ts_buy"] - full_df["ts_click"])
                    full_df.show()
                    full_df.select([c for c in full_df.columns() if c in columns])\
                        .write.format("org.apache.spark.sql.cassandra")\
                        .options(table="purchase_delta", keyspace=self._keyspace)\
                        .save(mode='append')
            except Exception as e:
                print("aggr_buy_click_delta full data persist failed", e)
                raise

            try:
                if full_df:
                    df = df.exceptAll(full_df)
                if df.count() > 0:
                    df = df.select([c for c in df.columns if c in columns])\
                        .write.format("org.apache.spark.sql.cassandra")\
                        .options(table="purchase_delta", keyspace=self._keyspace)\
                        .save(mode='append')
            except Exception as e:
                print("aggr_buy_click_delta persist failed", e)

        # TODO(zex): remove earlist
        click_ts = click.map(lambda x: ('-'.join([x['session_id'], x['item_id']]), x['timestamp']))\
                .reduceByKey(earlist)
        buy_ts = buy.map(lambda x: ('-'.join([x['session_id'], x['item_id']]), x['timestamp']))\
                .reduceByKey(earlist)
        price = buy.map(lambda x: ('-'.join([x['session_id'], x['item_id']]), x['price']))

        delta_ts = click_ts.fullOuterJoin(buy_ts).leftOuterJoin(price)
        delta_ts.foreachRDD(persist)

    def aggr_session_quan(self, buy):
        """session => quantity bought"""
        def persist(time, rdd):
            if len(rdd.collect()) == 0:
                return

            try:
                self._sess.createDataFrame(rdd, ["session_id", "quan_bought"])\
                    .write.format("org.apache.spark.sql.cassandra")\
                    .options(table="session_quan", keyspace=self._keyspace)\
                    .save(mode='append')
            except Exception as e:
                print("session_quan persist failed", e)

        sess_quan = buy.map(lambda x: (x['session_id'], x['quantity']))\
                .reduceByKey(lambda x,y: y+x)
        sess_quan.foreachRDD(persist)

    def aggr_session_click(self, click):
        """session => click count"""
        def persist(time, rdd):
            if len(rdd.collect()) == 0:
                return

            try:
                self._sess.createDataFrame(rdd, ["session_id", "click_count"])\
                    .write.format("org.apache.spark.sql.cassandra")\
                    .options(table="session_click", keyspace=self._keyspace)\
                    .save(mode='append')
            except Exception as e:
                print("session_click persist failed", e)

        click.map(lambda x: (x['session_id'], 1)).reduceByKey(lambda x,y: y+x)\
            .foreachRDD(persist)

    def aggr_item_click(self, click):
        """item => click count"""
        def persist(time, rdd):
            if len(rdd.collect()) == 0:
                return

            try:
                self._sess.createDataFrame(rdd, ["item_id", "click_count"])\
                    .write.format("org.apache.spark.sql.cassandra")\
                    .options(table="item_click", keyspace=self._keyspace)\
                    .save(mode='append')
            except Exception as e:
                print("item_click persist failed", e)

        click.map(lambda x: (x['item_id'], 1)).reduceByKey(lambda x,y: y+x)\
            .foreachRDD(persist)

    def aggr_item_quan(self, buy):
        """item => quantity bought"""
        def persist(time, rdd):
            if len(rdd.collect()) == 0:
                return
            try:
                self._sess.createDataFrame(rdd, ["item_id", "quan_bought"])\
                    .write.format("org.apache.spark.sql.cassandra")\
                    .options(table="item_quan", keyspace=self._keyspace)\
                    .save(mode='append')
            except Exception as e:
                print("item_quan persist failed", e)

        item_quan = buy.map(lambda x: (x['item_id'], x['quantity'])).reduceByKey(lambda x,y: y+x)
        item_quan.foreachRDD(persist)

    def persist_click(self, time, rdd):
        if len(rdd.collect()) == 0:
            return
        print('click', len(rdd.collect())) 
        try:
            df = self._sess.createDataFrame(rdd, ["category", "item_id", "session_id", "ts"])
            df.orderBy(df.ts.asc())\
                .write.format("org.apache.spark.sql.cassandra")\
                .options(table="click_event", keyspace=self._keyspace)\
                .save(mode='append')
        except Exception as e:
            print("click_event persist failed", e)

    def persist_buy(self, time, rdd):
        if len(rdd.collect()) == 0:
            return
        print('buy', len(rdd.collect())) 
        try:
            df = self._sess.createDataFrame(rdd, \
                    ["item_id", "price", "quantity", "session_id", "ts"])
            df.orderBy(df.ts.asc())\
                .write.format("org.apache.spark.sql.cassandra")\
                .options(table="buy_event", keyspace=self._keyspace)\
                .save(mode='append')
        except Exception as e:
            print("buy_event persist failed", e)
        
    def run(self):
        try:
            self._ssc.start()
            self._ssc.awaitTermination()
        except Py4JJavaError as e:
            print("start failed", e)
        except KeyboardInterrupt:
            print("shutdown")
        #    self._ssc.stop()
        except Exception as e:
            print("unhandled: ", e)

if __name__ == '__main__':
    app = ClickStreamAggr()
    app.run()
