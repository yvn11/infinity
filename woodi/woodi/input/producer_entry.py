# Feed dict producer for each data type
# Author: Zex Li <top_zlynch@yahoo.com>
import multiprocessing as mp
from woodi.common.topic import Topic
from woodi.common.config import get_config
from woodi.input.producers import *
import logging


def run_async(hdr_name):
    try:
        hdr = globals().get(hdr_name)()
        res = list(hdr.run_async())
        [print(r['future'].get()) for r in res]
    except KeyboardInterrupt:
        print("++ [terminate] {}".format(hdr_name))
    except Exception as ex:
        print("!! [error] {}".format(ex))
        raise

def start():
    pool = []
    try:
        for hdr_name in get_config().producers.split(','):
            pool.append(mp.Process(target=run_async,
                                    args=(hdr_name,),
                                    name=hdr_name,
                                    ))
        list(map(lambda p: p.start(), pool))
    except KeyboardInterrupt:
        #list(map(lambda p: p.join(), pool))
        print("++ [terminate]")
     

if __name__ == '__main__':
    start()
