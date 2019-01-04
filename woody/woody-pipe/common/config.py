# Service configure
# Author: Zex Li <top_zlynch@yahoo.com>
from os import environ as env
import string

class Config(object):

    def __init__(self):
        super(Config, self).__init__()
        self.load_config()

    def load_config(self):
        self.load_env()

    def load_env(self):
        _ = [setattr(self, k.lower().lstrip(string.digits+string.punctuation), v) \
                for k, v in env.items()]

    def raise_on_not_set(self, name):
        if not name:
            return

        if not hasattr(self, name):
            raise AttributeError("{} not set".format(name.upper()))

    def __str__(self):
        return '\n'.join(['{}:{}'.format(k, v) for k, v in self.__dict__.items()])

def get_config():
    if not globals().get('woody_config'):
        globals()['woody_config'] = Config()
    return globals().get('woody_config')
