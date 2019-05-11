#!/bin/bash

export PYTHONPATH=`pwd`
export CASSANDRA_SERVERS=10.1.10.5,10.1.10.7,10.1.10.9
export CASSANDRA_PORT=17001
export CASSANDRA_USER=dev
export CASSANDRA_PASS=`cat .dev_pass`
export KAFKA_BROKERS=10.1.10.5:17812,10.1.10.9:17812,10.1.10.8:17812
#export ZOO_SERVERS=10.1.10.5:2171,10.1.10.6:2171,10.1.10.9:2171
export SPARK_HOME=/opt/spark-2.4.0-bin-hadoop2.7
export SPARK_MASTER=local[2] #spark://10.1.10.5:18877
export SSC_DURATION=1
export PYSPARK_MAJOR_PYTHON_VERSION=3

#python3 phi/cassandra/aggr_cli.py
$SPARK_HOME/bin/spark-submit \
    --master $SPARK_MASTER \
    --conf spark.kubernetes.pyspark.pythonVersion=3 \
    --conf spark.streaming.kafka.maxRetries=100 \
    --conf spark.streaming.stopGracefullyOnShutdown=true \
    --packages com.datastax.spark:spark-cassandra-connector_2.11:2.4.0 \
    --jars /opt/spark-extern/spark-streaming-kafka-0-8-assembly_2.11-2.4.0.jar \
    -v \
    phi/apps/user_profile.py
