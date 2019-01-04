# Pipe definition
# Author: Zex Li <top_zlynch@yahoo.com>
from abc import abstractmethod


class Pipe(object):

    def __init__(self, **kwargs):
        super(Pipe, self).__init__()
        pass

    @abstractmethod
    def fetch(self, **kwargs):
        """Fetch from prior"""
        return kwargs

    @abstractmethod
    def send(self, **kwargs):
        """Send to next"""
        return kwargs

    @abstractmethod
    def convert(self, **kwargs):
        """Internal conversion"""
        return kwargs

    def run_async(self, **kwargs):
        """Asynchronous run, requires `fetch` to return generator"""
        for x in self.fetch(**kwargs):
            intm = self.convert(**x)
            yield self.send(**intm)

    def run(self, **kwargs):
        return self.send(**self.convert(**self.fetch(**kwargs)))

    def __call__(self, **kwargs):
        self.run(**kwargs)
