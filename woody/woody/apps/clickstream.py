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
import time

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

    def _summary(self):
        self.aggr_sum_click()
        self.aggr_buy_click()
        self.aggr_orderby_ts()

    def _from_kfk(self):
        # TODO: END_OF_STREAM EOFError
        kfk_params = {
            'metadata.broker.list': Config.kafka_brokers,
            'group.id': self.__class__.__name__,
            }
        self._click_ds = KafkaUtils.createDirectStream(self._ssc, ["click_ev"], kfk_params)
        self._buy_ds = KafkaUtils.createDirectStream(self._ssc, ["buy_ev"], kfk_params)
        # 2014-04-07T10:51:09.277Z
        fmt = "%Y-%m-%dT%H:%M:%S"#.%fZ"
        click = self._click_ds.map(lambda x: json.loads(x[1]))
        def click_conv(x):
            x['timestamp'] = datetime.strptime(x['timestamp'].split('.')[0], fmt)
            return x

        click = click.map(click_conv)
        click.foreachRDD(self.persist_click)

        self.aggr_session_click(click)
        #self.aggr_item_click(click)

        buy = self._buy_ds.map(lambda x: json.loads(x[1]))

        def buy_conv(x):
            x['price'] = float(x['price'])
            x['quantity'] = int(x['quantity'])
            x['timestamp'] = datetime.strptime(x['timestamp'].split('.')[0], fmt)
            return x
        buy = buy.map(buy_conv)
        buy.foreachRDD(self.persist_buy)
        
        # self.aggr_buy_click_delta(click, buy)
        #self.aggr_session_quan(buy)
        #self.aggr_item_quan(buy)
        #self._summary()

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

        def persist(tm, rdd):
            if len(rdd.collect()) == 0:
                return

            df, full_df = None, None

            try:
                rdd = rdd.map(lambda x: x[0].split('-') + [x[1][0][0],x[1][0][1]] + [x[1][1]])
                df = self._sess.createDataFrame(rdd, \
                          ["session_id", "item_id", "ts_click", "ts_buy", "price"])\
                        .dropDuplicates()
                full_df = df.dropna()
            except Exception as e:
                print("aggr_buy_click_delta transform failed", e)

            try:
                columns = ("item_id", "price", "ts_click", "ts_buy", "session_id", "ts_delta")
                if full_df.count() > 0:
                    full_df = full_df.withColumn("ts_delta", full_df["ts_buy"] - full_df["ts_click"])
                    full_df.select([c for c in full_df.columns() if c in columns])\
                      .write.format("org.apache.spark.sql.cassandra")\
                      .options(table="purchase_delta", keyspace=self._keyspace)\
                      .save(mode='overwrite')
            except Exception as e:
                print("aggr_buy_click_delta full data persist failed", e)

            try:
                if full_df:
                    df = df.exceptAll(full_df)
                if df.count() > 0:
                    df = df.select([c for c in df.columns if c in columns])\
                        .write.format("org.apache.spark.sql.cassandra")\
                        .options(table="purchase_delta", keyspace=self._keyspace)\
                        .save(mode='overwrite')
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
        opts = {"table":"session_quan", "keyspace":self._keyspace, "confirm.truncate":True}
        def persist(tm, rdd):
            if len(rdd.collect()) == 0:
                return

            try:
                df = self._sess.createDataFrame(rdd, ["session_id", "quan_bought"])
                df.write.format("org.apache.spark.sql.cassandra")\
                  .options(**opts)\
                  .save(mode='overwrite')
            except Exception as e:
                print("session_quan persist failed", e)

        sess_quan = buy.map(lambda x: (x['session_id'], x['quantity']))\
                .reduceByKey(lambda x,y: y+x)
        sess_quan.foreachRDD(persist)

    def aggr_session_click(self, click):
        """session => click count"""
        opts = {"table":"session_click", "keyspace":self._keyspace, "confirm.truncate":True}
        def persist(tm, rdd):
            if len(rdd.collect()) == 0:
                return

            try:
                df = self._sess.createDataFrame(rdd, ["sid", "new_count"])
                store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(table="session_click", keyspace=self._keyspace)\
                    .load()
                df = df.join(store_df, store_df.session_id==df.sid, 'outer')
                df = df.withColumnRenamed("click_count", "old_count")
                df = df.withColumn("click_count", df['old_count'] + df['new_count'])
                df = df.fillna(int(time.time()), ['created_at', 'updated_at'])
                df.show()

                df = df.select("session_id", "click_count", "created_at", "updated_at")
                df.show()
                df.write.format("org.apache.spark.sql.cassandra")\
                  .options(**opts)\
                  .save(mode='overwrite')
            except Exception as e:
                print("session_click persist failed", e)

        click.map(lambda x: (x['session_id'], 1)).reduceByKey(lambda x,y: y+x)\
            .foreachRDD(persist)
    
    def aggr_sum_click(self):
        click_df = None
        opts = {"table":"click_event", "keyspace":self._keyspace, "confirm.truncate":True} 

        try:
            click_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .load()
            print("total click: ", click_df.count())
        except Exception as e:
            print("failed to load click event", e)

        try:
            click_df.orderBy(click_df.session_id.asc(), click_df.ts.asc())\
                .write.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .save(mode='overwrite')
        except Exception as e:
            print("summary click event persist failed", e)

    def aggr_sum_buy(self):
        buy_df = None
        opts = {"table":"buy_event", "keyspace":self._keyspace, "confirm.truncate":True} 

        try:
            buy_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .load()
            print("total buy: ", buy_df.count())
        except Exception as e:
            print("failed to load buy event", e)

        try:
            buy_df.orderBy(buy_df.session_id.asc(), buy_df.ts.asc())\
                .write.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .save(mode='overwrite')
        except Exception as e:
            print("summary buy event persist failed", e)
    
    def aggr_item_click(self, click):
        """item => click count"""
        def persist(tm, rdd):
            if len(rdd.collect()) == 0:
                return

            try:
                df = self._sess.createDataFrame(rdd, ["item_id", "click_count"])
                opts = {"table":"item_click", "keyspace":self._keyspace, "confirm.truncate":True} 
                df.write.format("org.apache.spark.sql.cassandra")\
                  .options(**opts)\
                  .save(mode='overwrite')
            except Exception as e:
                print("item_click persist failed", e)

        click.map(lambda x: (x['item_id'], 1)).reduceByKey(lambda x,y: y+x)\
            .foreachRDD(persist)

    def aggr_item_quan(self, buy):
        """item => quantity bought"""
        def persist(tm, rdd):
            if len(rdd.collect()) == 0:
                return
            try:
                df = self._sess.createDataFrame(rdd, ["item_id", "quan_bought"])
                opts = {"table":"item_quan", "keyspace":self._keyspace, "confirm.truncate":True} 
                df.write.format("org.apache.spark.sql.cassandra")\
                  .options(**opts)\
                  .save(mode='overwrite')
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
            now = self._sess.createDataFrame([(datetime.now(),)]*df.count(), ['updated_at'])
            opts = {"table":"click_event", "keyspace":self._keyspace, "confirm.truncate":True} 
            df = df.orderBy(df.session_id.asc(), df.ts.asc())\
              .write.format("org.apache.spark.sql.cassandra")\
              .options(**opt)\
              .save(mode='overwrite')
        except Exception as e:
            print("click_event persist failed", e)

    def persist_buy(self, time, rdd):
        if len(rdd.collect()) == 0:
            return
        print('buy', len(rdd.collect())) 
        try:
            df = self._sess.createDataFrame(rdd, \
                    ["item_id", "price", "quantity", "session_id", "ts"])
            opts = {"table":"buy_event", "keyspace":self._keyspace, "confirm.truncate":True} 
            df.orderBy(df.session_id.asc(), df.ts.asc())\
              .write.format("org.apache.spark.sql.cassandra")\
              .options(opts)\
              .save(mode='overwrite')
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
