#!/usr/bin/python3
from pyspark.context import SparkContext
from pyspark.conf import SparkConf
from pyspark.streaming.context import StreamingContext
from pyspark.streaming.kafka import KafkaUtils
from pyspark.sql.types import IntegerType, StringType

from phi.common.config import Config
from phi.common.spark_utils import SparkSessionInstance, create_allocation_file, now_timestamp
from py4j.protocol import Py4JJavaError
from random import randint
import json
import numpy as np

class ProfileAggr(object):
    """Profile aggregates
    """
    def __init__(self):
        create_allocation_file(Config.spark_sched_file)
        conf = SparkConf()

        conf.set("spark.scheduler.allocation.file", Config.spark_sched_file)
        conf.set("spark.cassandra.connection.host", Config.cassandra_servers)
        conf.set("spark.cassandra.connection.port", Config.cassandra_port)
        conf.set("spark.cassandra.auth.username", Config.cassandra_user)
        conf.set("spark.cassandra.auth.password", Config.cassandra_pass)

        self._sc = SparkContext(appName=self.__class__.__name__+str(randint(10,20)), conf=conf)
        self._sc.setLogLevel('WARN')
        self._ssc = StreamingContext(self._sc, Config.ssc_duration)
        self._sess = SparkSessionInstance(conf)
        self._keyspace = "phi_userprofile"
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
        poi = self.poi(kfk_params)

        #city.foreachRDD(self.persist_city)
        poi.foreachRDD(self.persist_poi)
        #self.aggr_checkin(checkin)
    
    def persist_city(self, time, rdd):
        if rdd.count() == 0: return
        table = "city"
        opts = {"table":table, "keyspace":self._keyspace, 
                "spark.cassandra.input.split.size_in_mb": 1}
        now = now_timestamp()
        cols = ["country_code", "country_name", "created_at", "lat", "lon", "name", "ctype", "updated_at"]

        try:
            df = self._sess.createDataFrame(rdd, cols)
            df.show()
            df.write.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .save(mode='ignore')
        except Exception as ex:
            print('persist failed: {}: {}'.format(table, ex))

    def persist_poi(self, time, rdd):
        if rdd.count() == 0: return
        table = "poi"
        opts = {"table":table, "keyspace":self._keyspace, 
                "spark.cassandra.input.split.size_in_mb": 1}
        now = now_timestamp()
        cols = ["country_code", "created_at", "lat", "lon", "updated_at", "venue_cate", "venue_id"]
        
        try:
            df = self._sess.createDataFrame(rdd, cols)
            df.write.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .save(mode='ignore')
        except Exception as ex:
            print('persist failed: {}: {}'.format(table, ex))

    def aggr_checkin(self, checkin):
        checkin.map(lambda x: (x['user_id'], 1)).reduceByKey(lambda x, y: x+y)\
            .foreachRDD(self.persist_user_checkin)

        checkin.map(lambda x: (x['venue_id'], 1)).reduceByKey(lambda x, y: x+y)\
            .foreachRDD(self.persist_venue_checkin)

        # TODO(zex): map to city
        #checkin.map(lambda x: 1).reduceByKey(lambda x, y: x+y)\
        #    .foreachRDD(persist)

    def persist_user_checkin(self, time, rdd):
        if rdd.count() == 0: return

        opts = {"table":"user_checkin_count", "keyspace":self._keyspace}
                #"spark.cassandra.input.split.size_in_mb": 1
        now = now_timestamp()
        store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .load()
        try:
            df = self._sess.createDataFrame(rdd, ["uid", "new_count"])
            df = df.join(store_df, store_df.user_id==df.uid, "outer")\
                .withColumnRenamed("checkin_count", "old_count")\
                .na.fill({"old_count":0,"updated_at":now,"created_at":now,"lat":0.0,"lon":0.0})
            df = df.withColumn("checkin_count", df["new_count"] + df["old_count"])\
                    .drop("user_id").withColumnRenamed("uid", "user_id")\
                    .drop("new_count").drop("old_count").na.drop()
            df.show(100)
            df.write.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .save(mode='append')
        except Exception as ex:
            print('persist failed: user_checkin: {}'.format(ex))

    def persist_city_checkin(self, checkin):
        if rdd.count() == 0: return

        opts = {"table":"city_checkin_count", "keyspace":self._keyspace,
                "spark.cassandra.input.split.size_in_mb": 1}
    
        now = now_timestamp()
        store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .load()
        try: 
            df = self._sess.createDataFrame(rdd, ["cname", "new_count"])
            df = df.join(store_df, store_df.city_name==df.cname, "outer")\
                .withColumnRenamed("checkin_count", "old_count")\
                .na.fill({"old_count":0,"updated_at":now,"created_at":now,"lat":0.0,"lon":0.0})
            df = df.withColumn("checkin_count", df["new_count"] + df["old_count"])\
                .drop("city_name").withColumnRenamed("cname", "city_name")\
                .drop("new_count").drop("old_count").na.drop()\
                .write.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .save(mode='append')
        except Exception as ex:
            print('persist failed: city_checkin: {}'.format(ex))

    def persist_venue_checkin(self, time, rdd):
        if rdd.count() == 0: return
        opts = {"table":"venue_checkin_count", "keyspace":self._keyspace,
                "spark.cassandra.input.split.size_in_mb": 1}
    
        now = now_timestamp()
        store_df = self._sess.read.format("org.apache.spark.sql.cassandra")\
                .options(**opts)\
                .load()
        try:
            df = self._sess.createDataFrame(rdd, ["vid", "new_count"])
            df = df.join(store_df, store_df.venue_id==df.vid, "outer")\
                .withColumnRenamed("checkin_count", "old_count")\
                .na.fill({"old_count":0,"updated_at":now,"created_at":now,"lat":0.0,"lon":0.0})
            df = df.withColumn("checkin_count", df["new_count"] + df["old_count"])\
                .drop("venue_id").withColumnRenamed("vid", "venue_id")\
                .drop("new_count").drop("old_count").drop("vid").na.drop()\
                .write.format("org.apache.spark.sql.cassandra")\
                    .options(**opts)\
                    .save(mode='append')
        except Exception as ex:
            print('persist failed: venue_checkin: {}'.format(ex))

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
