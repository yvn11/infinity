# Prediction consumer for each data type
# Author: Zex Li <top_zlynch@yahoo.com>
import os
import ujson
import numpy as np
import pandas as pd
from boto3.dynamodb.conditions import Key, Attr
from woodi.output.consumer import Prediction as PC
from woodi.common.config import get_config
from woodi.common.topic import Topic
from src.dynamodb.core.broker import get_brk
from src.dynamodb.tables.journal_article import JournalIMsg
from src.dynamodb.tables.tech_classi import TechClassi


class IMsg(PC):
    """Prediction consumer for article"""
    def __init__(self, **kwargs):
        super(IMsg, self).__init__(topics=(Topic.CHAT_IMSG,),  **kwargs)
        self.recv_cnt = 0

    def send(self, **kwargs):
        self.recv_cnt += 1
        user_id = kwargs.get('user_id')
        msg = kwargs['msg']

        print("[{}] user_id:{} msg:[{}]".format(self.recv_cnt, user_id, msg)
