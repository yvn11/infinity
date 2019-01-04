# Output producer
# Author: Zex Li <top_zlynch@yahoo.com>
import os
from kafka import KafkaConsumer
import msgpack
from woody.common.config import get_config
from woody.output.base import Output
from woody.common.topic import Topic


class Prediction(Output):
    """Prediction Consumer"""
    def __init__(self, *args, **kwargs):
        super(Prediction, self).__init__()
        brokers = get_config().kafka_brokers.split(',')
        client_id = kwargs.get('client_id')

        kw = {
                'bootstrap_servers': brokers,
                'value_deserializer': msgpack.unpackb,
            }

        if client_id:
            kw['client_id'] = client_id

        self.topics = kwargs.get('topics')
        self.cons = KafkaConsumer(*self.topics, **kw)

    def __del__(self):
        if hasattr(self, 'con') and self.cons:
            self.cons.close()

    def fetch(self, **kwargs):
        """Fetch results from model"""
        for msg in self.cons:
            data = msgpack.unpackb(msg.value)
            data = {k.decode():v for k, v in data.items()}
            yield data

    def send(self, **kwargs):
        """Write back to database
        """
        return kwargs

    def convert(self, **kwargs):
        """Internal conversion"""
        return kwargs

    def run_async(self, **kwargs):
        """Asynchronous run, requires `fetch` to return generator"""
        for x in self.fetch(**kwargs):
            for intm in self.convert(**x):
                if intm:
                    yield self.send(**intm)

    def __del__(self):
        cons = getattr(self, 'cons', None)
        if cons:
            cons.close()
