#!/bin/bash

export PYTHONPATH=`pwd`
export CASSANDRA_SERVERS=192.168.70.220,192.168.70.203,192.168.70.35
export CASSANDRA_PORT=17001
export CASSANDRA_USER=dev
export CASSANDRA_PASS=`cat .dev_pass`
export KAFKA_BROKERS=192.168.70.220:17812,192.168.70.35:17812,192.168.70.94:17812
#export ZOO_SERVERS=192.168.70.220:2171,192.168.70.189:2171,192.168.70.35:2171
export SPARK_HOME=/opt/spark-2.4.0-bin-hadoop2.7
export SPARK_MASTER=local[2] #spark://192.168.70.220:18877
export SSC_DURATION=1
export PYSPARK_MAJOR_PYTHON_VERSION=3

#python3 woody/cassandra/aggr_cli.py
$SPARK_HOME/bin/spark-submit \
    --master $SPARK_MASTER \
    --conf spark.kubernetes.pyspark.pythonVersion=3 \
    --conf spark.streaming.kafka.maxRetries=100 \
    --conf spark.streaming.stopGracefullyOnShutdown=true \
    --packages com.datastax.spark:spark-cassandra-connector_2.11:2.4.0 \
    --jars /opt/spark-extern/spark-streaming-kafka-0-8-assembly_2.11-2.4.0.jar \
    -v \
    woody/apps/user_profile.py
