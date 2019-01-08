from pyspark.context import SparkContext
from pyspark.streaming.context import StreamingContext
from pyspark.streaming.kafka import KafkaUtils
from woody.common.config import Config
from py4j.protocol import Py4JJavaError

class ProfileAggr(object):
    """Profile aggregates
    """
    def __init__(self):
        self._sc = SparkContext(appName=self.__class__.__name__)
        self._sc.setLogLevel('WARN')
        self._ssc = StreamingContext(self._sc, Config.ssc_duration)
        self._from_kfk()

    def _from_kfk(self):
        kfk_params = {
            'metadata.broker.list': Config.kafka_brokers,
            'group.id': self.__class__.__name__,
            }
        """
        self._ds = KafkaUtils.createStream(self._ssc, Config.zoo_servers, 
            self.__class__.__name__,
            {"user_imsg": 3})
        """
        print(kfk_params)
        self._ds = KafkaUtils.createDirectStream(self._ssc, ["user_imsg"], kfk_params)
        self._ds.foreachRDD(self.foreach_rdd)
	"""
        lines = self._ds.map(lambda x: x[1])
        lines.pprint()
        lines.saveAsTextFiles(self.__class__.__name__)
        """     
    def foreach_rdd(self, time, rdd):
        print(time, rdd)
        #TODO

    def run(self):
        try:
            self._ssc.start()
            self._ssc.awaitTermination()
        except Py4JJavaError as e:
            print("start failed", e)
        except KeyboardInterrupt:
            print("shutdown")
            self._ssc.stop()

if __name__ == '__main__':
    app = ProfileAggr()
    app.run()
