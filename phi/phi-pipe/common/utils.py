# Utilities
# Author: Zex Li <top_zlynch@yahoo.com>
import os

def raise_if_not_found(path):
    if not os.path.isfile(path):
        raise FileNotFoundError(path)
