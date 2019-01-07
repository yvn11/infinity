#!/bin/bash

export PYTHONPATH=`pwd`
export CASSANDRA_SERVERS=192.168.70.220,192.168.70.189,192.168.70.35
export CASSANDRA_PORT=17001
export CASSANDRA_USER=
export CASSANDRA_PASS=

python3 woody/cassandra/aggr_cli.py
