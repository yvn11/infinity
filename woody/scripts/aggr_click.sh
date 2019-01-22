#!/bin/bash

export PYTHONPATH=`pwd`:/usr/local/lib64/python3.6/site-packages:/usr/lib/python3.6/site-packages:/usr/local/lib64/python3.6/site-packages/cassandra
export CASSANDRA_SERVERS=192.168.70.220,192.168.70.189,192.168.70.35
export CASSANDRA_PORT=17001
export CASSANDRA_USER=dev
export CASSANDRA_PASS=dcb5c69fedb78e9a29a3
export KAFKA_BROKERS=192.168.70.220:17812 #,192.168.70.35:17812,192.168.70.94:17812
#export ZOO_SERVERS=192.168.70.220:2171,192.168.70.189:2171,192.168.70.35:2171
export SPARK_HOME=/opt/spark-2.4.0-bin-hadoop2.7
#export SPARK_MASTER=k8s://https://192.168.70.140:6443
export SPARK_MASTER=local[4] #yarn
#export PYSPARK_PYTHON=/usr/bin/python3
#local[4] #spark://192.168.70.220:18877
export SSC_DURATION=1

     #/opt/spark-extern/spark-cassandra-connector-2.4.0-s_2.11.jar \
#python3 woody/cassandra/aggr_cli.py
$SPARK_HOME/bin/spark-submit \
    --master $SPARK_MASTER \
    --packages com.datastax.spark:spark-cassandra-connector_2.11:2.4.0 \
    --deploy-mode client \
    --conf spark.executor.instances=2 \
    --conf spark.kubernetes.container.image=zlynch/spark:2.4.0 \
    --conf spark.kubernetes.authenticate.driver.serviceAccountName=spark \
    --conf spark.cassandra.connection.host=$CASSANDRA_SERVERS \
    --conf spark.cassandra.connection.port=$CASSANDRA_PORT \
    --conf spark.cassandra.input.consistency.level=ONE \
    --conf spark.cassandra.output.consistency.level=ONE \
    --jars /opt/spark-extern/spark-streaming-kafka-0-8-assembly_2.11-2.4.0.jar \
    woody/apps/clickstream.py
