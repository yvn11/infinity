# Prediction consumer for each data type
# Author: Zex Li <top_zlynch@yahoo.com>
import multiprocessing as mp
from phi.common.config import get_config
from phi.output.consumers import *


def run_async(hdr_name):
    try:
        hdr = globals().get(hdr_name)()
        _ = list(hdr.run_async())
    except KeyboardInterrupt:
        print("++ [terminate] {}".format(hdr_name))
    except Exception as ex:
        print("-- [error] {}".format(ex))


def start():
    pool = []
    try:
        for hdr_name in get_config().consumers.split(','):
            pool.append(mp.Process(target=run_async,
                                    args=(hdr_name,),
                                    name=hdr_name))
        list(map(lambda p: p.start(), pool))
    except KeyboardInterrupt:
        list(map(lambda p: p.join(), pool))
        print("++ [terminate]")


if __name__ == '__main__':
    start()
