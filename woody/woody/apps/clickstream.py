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

        self._sc = SparkContext(appName=self.__class__.__name__+str(randint(10,20)), conf=conf)
        self._sc.setLogLevel('WARN')
        self._ssc = StreamingContext(self._sc, Config.ssc_duration)
        self._sess = SparkSessionInstance(conf)
        self._keyspace = "woody_clickstream"
        # 2014-04-07T10:51:09.277Z
        self._from_kfk()

    def _summary(self):
        self.aggr_sum_click()
        self.aggr_buy_click()
        self.aggr_orderby_ts()

    def click_event(self, tsfmt, kfk_params):
        click = KafkaUtils.createDirectStream(self._ssc, ["click_ev"], kfk_params)\
                .map(lambda x: json.loads(x[1]))
        def click_conv(x):
            x['timestamp'] = datetime.strptime(x['timestamp'].split('.')[0], tsfmt)
            return x
        return click.map(click_conv)

    def buy_event(self, tsfmt, kfk_params):
        buy = KafkaUtils.createDirectStream(self._ssc, ["buy_ev"], kfk_params)\
            .map(lambda x: json.loads(x[1]))
        def buy_conv(x):
            x['price'] = float(x['price'])
            x['quantity'] = int(x['quantity'])
            x['timestamp'] = datetime.strptime(x['timestamp'].split('.')[0], tsfmt)
            return x
        return buy.map(buy_conv)

    def _from_kfk(self):

        tsfmt = "%Y-%m-%dT%H:%M:%S"#.%fZ"
        kfk_params = {
            'metadata.broker.list': Config.kafka_brokers,
            #'group.id': self.__class__.__name__,
            }

        # TODO: END_OF_STREAM EOFError
        click = self.click_event(tsfmt, kfk_params)
        buy = self.buy_event(tsfmt, kfk_params)

        click.foreachRDD(self.aggr_click_per_sec)
        buy.foreachRDD(self.aggr_buy_per_sec)

        #self.aggr_category_click(click)
        #self.aggr_session_click(click)
        #self.aggr_item_click(click)

        #self.aggr_session_quan(buy)
        #self.aggr_item_quan(buy)
        # self.aggr_buy_click_delta(click, buy)
        # self._summary()

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
            if rdd.count() == 0:
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
                      .save(mode='append')
            except Exception as e:
                print("aggr_buy_click_delta full data persist failed", e)

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
        opts = {"table":"session_quan", "keyspace":self._keyspace, "confirm.truncate":"true"}
        def persist(tm, rdd):
            if rdd.count() == 0:
                return

            try:
                df = self._sess.createDataFrame(rdd, ["sid", "new_quan"])
                store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(table="session_quan", keyspace=self._keyspace)\
                    .load()
                df = df.join(store_df, store_df.session_id==df.sid, 'outer')
                df = df.withColumnRenamed("quan_bought", "old_quan")
                now = int(time.mktime(datetime.utcnow().timetuple()))
                df = df.na.fill({'old_quan':0,'updated_at':now,'created_at':now})
                df = df.withColumn("quan_bought", df['old_quan'] + df['new_quan'])
                df = df.drop("session_id").drop('old_quan').drop('new_quan')
                df = df.withColumnRenamed("sid", "session_id")
                df = df.na.drop()
                df.write.format("org.apache.spark.sql.cassandra")\
                  .options(**opts)\
                  .save(mode='append')
            except Exception as e:
                print("session_quan persist failed", e)

        sess_quan = buy.map(lambda x: (x['session_id'], x['quantity']))\
                .reduceByKey(lambda x,y: y+x)
        sess_quan.foreachRDD(persist)

    def aggr_session_click(self, click):
        """session => click count"""
        opts = {"table":"session_click", "keyspace":self._keyspace, "confirm.truncate":"true"}
        def persist(tm, rdd):
            if rdd.count() == 0:
                return

            try:
                df = self._sess.createDataFrame(rdd, ["sid", "new_count"])
                store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(table="session_click", keyspace=self._keyspace)\
                    .load()
                df = df.join(store_df, store_df.session_id==df.sid, 'outer')
                df = df.withColumnRenamed("click_count", "old_count")
                now = int(time.mktime(datetime.utcnow().timetuple()))
                df = df.na.fill({'old_count':0,'updated_at':now,'created_at':now})
                df = df.withColumn("click_count", df['old_count'] + df['new_count'])
                df = df.drop("session_id").drop('old_count').drop('new_count')
                df = df.withColumnRenamed("sid", "session_id")
                df = df.na.drop()
                df.write.format("org.apache.spark.sql.cassandra")\
                  .options(**opts)\
                  .save(mode='append')
            except Exception as e:
                print("session_click persist failed", e)

        click.map(lambda x: (x['session_id'], 1)).reduceByKey(lambda x,y: y+x)\
            .foreachRDD(persist)

    def aggr_category_click(self, click):
        """category => click count"""
        opts = {"table":"category_click", "keyspace":self._keyspace, "confirm.truncate":"true"}
        def persist(tm, rdd):
            if rdd.count() == 0:
                return

            try:
                """
                df = self._sess.createDataFrame(rdd, ["cate", "new_count"])
                store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(table="category_click", keyspace=self._keyspace)\
                    .load()
                df = df.join(store_df, store_df.category==df.cate, 'outer')
                df = df.withColumnRenamed("click_count", "old_count")
                now = int(time.mktime(datetime.utcnow().timetuple()))
                df = df.na.fill({'old_count':0,'updated_at':now,'created_at':now})
                df = df.withColumn("click_count", df['old_count'] + df['new_count'])
                df = df.drop("category").drop('old_count').drop('new_count')
                df = df.withColumnRenamed("cate", "category")
                df.show()
                df = df.na.drop()
                """
                df = self._sess.createDataFrame(rdd, ["category", "click_count"])
                df.write.format("org.apache.spark.sql.cassandra")\
                  .options(**opts)\
                  .save(mode='append')
            except Exception as e:
                print("category_click persist failed", e)

        click.map(lambda x: (x['category'], 1)).reduceByKey(lambda x,y: y+x)\
            .foreachRDD(persist)

    def aggr_sum_click(self):
        click_df = None
        opts = {"table":"click_event", "keyspace":self._keyspace, "confirm.truncate":"true"}

        try:
            click_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .load()
            print("total event: ", click_df.count())
        except Exception as e:
            print("failed to load click event", e)

        try:
            click_df.orderBy(click_df.session_id.asc(), click_df.ts.asc())\
                .write.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .save(mode='append')
        except Exception as e:
            print("summary click event persist failed", e)

    def aggr_sum_buy(self):
        buy_df = None
        opts = {"table":"buy_event", "keyspace":self._keyspace, "confirm.truncate":"true"}

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
                .save(mode='append')
        except Exception as e:
            print("summary buy event persist failed", e)

    def aggr_item_click(self, click):
        """item => click count"""
        opts = {"table":"item_click", "keyspace":self._keyspace, "confirm.truncate":"true"}
        def persist(tm, rdd):
            if rdd.count() == 0:
                return

            try:
                df = self._sess.createDataFrame(rdd, ["iid", "new_count"])
                store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(table="item_click", keyspace=self._keyspace)\
                    .load()
                df = df.join(store_df, store_df.item_id==df.iid, 'outer')
                df = df.withColumnRenamed("click_count", "old_count")
                now = int(time.mktime(datetime.utcnow().timetuple()))
                df = df.na.fill({'old_count':0,'updated_at':now,'created_at':now})
                df = df.withColumn("click_count", df['old_count'] + df['new_count'])
                df = df.drop("item_id").drop('old_count').drop('new_count')
                df = df.withColumnRenamed("iid", "item_id")
                df = df.na.drop()
                df.write.format("org.apache.spark.sql.cassandra")\
                  .options(**opts)\
                  .save(mode='append')
            except Exception as e:
                print("item_click persist failed", e)

        click.map(lambda x: (x['item_id'], 1)).reduceByKey(lambda x,y: y+x)\
            .foreachRDD(persist)

    def aggr_item_quan(self, buy):
        """item => quantity bought"""
        opts = {"table":"item_quan", "keyspace":self._keyspace, "confirm.truncate":"true"}
        def persist(tm, rdd):
            if rdd.count() == 0:
                return
            try:
                df = self._sess.createDataFrame(rdd, ["iid", "new_quan"])
                store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(table="item_quan", keyspace=self._keyspace)\
                    .load()
                df = df.join(store_df, store_df.item_id==df.iid, 'outer')
                df = df.withColumnRenamed("quan_bought", "old_quan")
                now = int(time.mktime(datetime.utcnow().timetuple()))
                df = df.na.fill({'old_quan':0,'updated_at':now,'created_at':now})
                df = df.withColumn("quan_bought", df['old_quan'] + df['new_quan'])
                df = df.drop("item_id").drop('old_quan').drop('new_quan')
                df = df.withColumnRenamed("iid", "item_id")
                df = df.na.drop()
                df.write.format("org.apache.spark.sql.cassandra")\
                  .options(**opts)\
                  .save(mode='append')
            except Exception as e:
                print("item_quan persist failed", e)

        item_quan = buy.map(lambda x: (x['item_id'], x['quantity'])).reduceByKey(lambda x,y: y+x)
        item_quan.foreachRDD(persist)

    def aggr_click_per_sec(self, tm, rdd):
        if rdd.count() == 0: return

        print('click', rdd.count())
        opts = {"table":"total_event", "keyspace":self._keyspace, "confirm.truncate":"true"}
        now = int(time.mktime(datetime.now().timetuple()))

        try:
            df = self._sess.createDataFrame([('click', tm, rdd.count())], ["event", "ts", "count"])
            df.write.format("org.apache.spark.sql.cassandra")\
              .options(**opts)\
              .save(mode='append')
        except Exception as e:
            print("total_event persist failed", e)

        opts = {"table":"click_event", "keyspace":self._keyspace, "confirm.truncate":"true"}

        try:
            df = self._sess.createDataFrame(rdd, ["category", "item_id", "session_id", "ts"])
            df = df.orderBy(df.session_id.asc(), df.ts.asc())\
              .write.format("org.apache.spark.sql.cassandra")\
              .options(**opts)\
              .save(mode='append')
        except Exception as e:
            print("click_event persist failed", e)

    def aggr_buy_per_sec(self, tm, rdd):
        if rdd.count() == 0: return
        print('buy', rdd.count())

        opts = {"table":"total_event", "keyspace":self._keyspace, "confirm.truncate":"true"}
        now = int(time.mktime(datetime.now().timetuple()))

        try:
            df = self._sess.createDataFrame([('buy', tm, rdd.count())], ["event", "ts", "count"])
            df.write.format("org.apache.spark.sql.cassandra")\
              .options(**opts)\
              .save(mode='append')
        except Exception as e:
            print("total_event persist failed", e)

        opts = {"table":"buy_event", "keyspace":self._keyspace, "confirm.truncate":"true"}

        try:
            df = self._sess.createDataFrame(rdd, \
                    ["item_id", "price", "quantity", "session_id", "ts"])
            df.orderBy(df.session_id.asc(), df.ts.asc())\
              .write.format("org.apache.spark.sql.cassandra")\
              .options(**opts)\
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
