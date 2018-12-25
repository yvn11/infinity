# Feed dict producer for each instant message
# Author: Zex Li <top_zlynch@yahoo.com>
import random
from woodi.input.producer import FeedDict as FDProducer
from woodi.common.topic import Topic
from woodi.common.config import get_config
from woodi.common.shared import Default
import logging


class IMsg(FDProducer):

    def __init__(self, **kwargs):
        super(IMsg, self).__init__(topic=Topic.CHAT_IMSG, **kwargs)
        self.total = 0
        self.chat_db = ["ok","fine","go ahead","good morning"]

    def fetch(self, **kwargs):
        iid = 0xdeadbeaf
        for _ in range(100):
            yield {
                 'user_id': iid,
                 'msg': self.rand_msg(),
                 }

    def rand_msg(self):
        return self.chat_db[random.randint(0, len(self.chat_db))]
