from cassandra.cluster import Cluster
from phi.common.config import Config

class Client:

    def __init__(self):
        pass

    def cleanup(self):
        pass

    def __del__(self):
        self.cleanup()

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.cleanup()
