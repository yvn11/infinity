#!/usr/bin/python3
from pyspark.context import SparkContext
from pyspark.conf import SparkConf
from pyspark.streaming.context import StreamingContext
from pyspark.streaming.kafka import KafkaUtils

from woody.common.config import Config
from woody.common.spark_utils import SparkSessionInstance, create_allocation_file
from py4j.protocol import Py4JJavaError
from datetime import datetime
from random import randint

class ProfileAggr(object):
    """Profile aggregates
    """
    def __init__(self):
        create_allocation_file(Config.spark_sched_file)
        conf = SparkConf()

        conf.set("spark.scheduler.allocation.file", Config.spark_sched_file)
        conf.set("spark.cassandra.auth.username", Config.cassandra_user)
        conf.set("spark.cassandra.auth.password", Config.cassandra_pass)

        self._sc = SparkContext(appName=self.__class__.__name__+str(randint(10,20)), conf=conf)
        self._sc.setLogLevel('WARN')
        self._ssc = StreamingContext(self._sc, Config.ssc_duration)
        self._sess = SparkSessionInstance(conf)
        self._keyspace = "woody_userprofile"
        self._from_kfk()

    def checkin(self, kfk_params):
        return KafkaUtils.createDirectStream(self._ssc, ["checkin_ev"], kfk_params)\
                .map(lambda x: json.loads(x[1]))
                
    def city(self, kfk_params):
        return KafkaUtils.createDirectStream(self._ssc, ["city_ev"], kfk_params)\
                .map(lambda x: json.loads(x[1]))

    def poi(self, kfk_params):
        return KafkaUtils.createDirectStream(self._ssc, ["poi_ev"], kfk_params)\
                .map(lambda x: json.loads(x[1]))
        
    def _from_kfk(self):
        kfk_params = {
            'metadata.broker.list': Config.kafka_brokers,
            #'group.id': self.__class__.__name__,
            }
        checkin = self.checkin(kfk_params)
        city = self.city(kfk_params)
        poi = self.city(kfk_params)

        self.ignore_persist(city, ["name", "ctype", "country_code", "country_name", "lat", "lon"])
        self.ignore_persist(poi, ["venue_id", "venue_cate", "country_code", "lat", "lon"])
        self.aggr_user_checkin(checkin)
        self.aggr_city_checkin(checkin)
    
    def ignore_persist(self, table, cols):
        def persist(time, rdd):
            if rdd.count() == 0: return
            opts = {"table":table, "keyspace":self._keyspace, 
                    "spark.cassandra.input.split.size_in_mb": 1}
            now = int(datetime.now().timestamp())
            store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .load()
            df = self._sess.createDataFrame(rdd, cols)\
                    .join(store_df, how="outer")\
                    .na.fill({"updated_at":now,"created_at":now})\
                    .write.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .save(mode='ignore')
            
        table.foreachRDD(persist)

    def aggr_user_checkin(self, checkin):
        def persist(time, rdd):
            if rdd.count() == 0: return
            opts = {"table":"user_checkin_count", "keyspace":self._keyspace,
                    "spark.cassandra.input.split.size_in_mb": 1}
        
            now = int(datetime.now().timestamp())
            store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .load()
            df = self._sess.createDataFrame(rdd, ["uid", "new_count"])\
                .join(store_df, store_df.user_id==df.uid, "outer")\
                .na.fill({"old_count":0,"updated_at":now,"created_at":now})
            df = df.withColumnRenamed("checkin_count", "old_count")\
                    .withColumn("checkin_count", df["new_count"] + df["checkin_count"])\
                    .drop("new_count").drop("old_count").drop("uid").na.drop()
            df.write.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .save(mode='append')
        checkin.map(lambda x: 1).reduceByKey(lambda x, y: x+y)\
            .foreachRDD(persist)

    def aggr_city_checkin(self, checkin):
        def persist(time, rdd):
            if rdd.count() == 0: return
            opts = {"table":"city_checkin_count", "keyspace":self._keyspace,
                    "spark.cassandra.input.split.size_in_mb": 1}
        
            now = int(datetime.now().timestamp())
            store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .load()
            df = self._sess.createDataFrame(rdd, ["cname", "new_count"])\
                .join(store_df, store_df.city_name==df.cname, "outer")\
                .na.fill({"old_count":0,"updated_at":now,"created_at":now})
            df = df.withColumnRenamed("checkin_count", "old_count")\
                    .withColumn("checkin_count", df["new_count"] + df["checkin_count"])\
                    .drop("new_count").drop("old_count").drop("cname").na.drop()
            df.write.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .save(mode='append')
        checkin.map(lambda x: 1).reduceByKey(lambda x, y: x+y)\
            .foreachRDD(persist)

    def aggr_venue_checkin(self, checkin):
        def persist(time, rdd):
            if rdd.count() == 0: return
            opts = {"table":"venue_checkin_count", "keyspace":self._keyspace,
                    "spark.cassandra.input.split.size_in_mb": 1}
        
            now = int(datetime.now().timestamp())
            store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .load()
            df = self._sess.createDataFrame(rdd, ["vid", "new_count"])\
                .join(store_df, store_df.venue_id==df.vid, "outer")\
                .na.fill({"old_count":0,"updated_at":now,"created_at":now})
            df = df.withColumnRenamed("checkin_count", "old_count")\
                    .withColumn("checkin_count", df["new_count"] + df["checkin_count"])\
                    .drop("new_count").drop("old_count").drop("vid").na.drop()
            df.write.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .save(mode='append')
        checkin.map(lambda x: 1).reduceByKey(lambda x, y: x+y)\
            .foreachRDD(persist)

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
    app = ProfileAggr()
    app.run()
