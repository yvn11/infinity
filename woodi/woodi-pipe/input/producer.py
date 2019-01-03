# Input producer
# Author: Zex Li <top_zlynch@yahoo.com>
import msgpack
from kafka import KafkaProducer
from woodi.common.config import get_config
from woodi.input.base import Input


class FeedDict(Input):
    """Feed dict producer"""
    def __init__(self, **kwargs):
        super(FeedDict, self).__init__(**kwargs)
        brokers = get_config().kafka_brokers.split(',')
        self.topic = kwargs.get('topic')
        client_id = kwargs.get('client_id')

        kw = {
                'bootstrap_servers': brokers,
                'value_serializer': msgpack.dumps,
            }

        if client_id:
            kw['client_id'] = client_id

        self.pro = KafkaProducer(**kw)

    def __del__(self):
        if hasattr(self, 'pro') and self.pro:
            self.pro.flush()
            self.pro.close()

    def fetch(self, **kwargs):
        """Fetch resource from database"""
        yield kwargs

    def send(self, **kwargs):
        """Send to broker
        Args:

        id: unique ID
        input_x: Batch of raw text for data provider
        """
        return {'future':self.pro.send(self.topic, msgpack.dumps(kwargs))}

    def convert(self, **kwargs):
        """Internal conversion"""
        return kwargs

    def __del__(self):
        pro = getattr(self, 'pro', None)
        if pro:
            pro.close()
