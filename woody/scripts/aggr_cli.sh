#!/bin/bash

export PYTHONPATH=`pwd`
export CASSANDRA_SERVERS=192.168.70.220,192.168.70.189,192.168.70.35
export CASSANDRA_PORT=17001
export CASSANDRA_USER=
export CASSANDRA_PASS=
export KAFKA_BROKERS=192.168.70.220:17812,192.168.70.35:17812,192.168.70.94:17812
#export ZOO_SERVERS=192.168.70.220:2171,192.168.70.189:2171,192.168.70.35:2171
export SPARK_HOME=/opt/spark-2.4.0-bin-hadoop2.7

#python3 woody/cassandra/aggr_cli.py
#python3 woody/apps/profile_aggr.py
$SPARK_HOME/bin/spark-submit \
    --jars /opt/spark-extern/spark-streaming-kafka-0-8-assembly_2.11-2.4.0.jar \
    woody/apps/profile_aggr.py
