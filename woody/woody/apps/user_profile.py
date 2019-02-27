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

    def _from_kfk(self):
        kfk_params = {
            'metadata.broker.list': Config.kafka_brokers,
            #'group.id': self.__class__.__name__,
            }

    def foreach_rdd(self, time, rdd):
        print(time, rdd)

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
