#!/bin/bash

# TODO: ns lookup
# with IPs, servers must be configured manually on each node by setting self to 0.0.0.0
#--env ZOO_SERVERS="server.1=192.168.100.203:2888:3888 server.2=192.168.100.189:2888:3888 server.3=192.168.100.220:2888:3888" \
#--mount type=bind,source=/zk-conf,target=/conf \

docker service create \
  --name zk1 \
  --network core-overlay \
  --publish mode=host,published=2171,target=2181 \
  --publish mode=host,published=2878,target=2888 \
  --publish mode=host,published=3878,target=3888 \
  --mount type=volume,source=zk-data,target=/data \
  --mount type=volume,source=zk-datalog,target=/datalog \
  --mount type=volume,source=zk-logs,target=/logs \
  -e ZOO_MY_ID=1 \
  -e ZOO_SERVERS="server.1=0.0.0.0:2888:3888;2181 server.2=192.168.100.189:2878:3878 server.3=192.168.100.203:2878:3878" \
  --constraint node.labels.zknode==1 \
  --replicas 1 \
  zookeeper:3.5
docker service create \
  --name zk2 \
  --network core-overlay \
  --publish mode=host,published=2171,target=2181 \
  --publish mode=host,published=2878,target=2888 \
  --publish mode=host,published=3878,target=3888 \
  --mount type=volume,source=zk-data,target=/data \
  --mount type=volume,source=zk-datalog,target=/datalog \
  --mount type=volume,source=zk-logs,target=/logs \
  --constraint node.labels.zknode==2 \
  -e ZOO_MY_ID=2 \
  -e ZOO_SERVERS="server.1=192.168.100.220:2878:3878 server.2=0.0.0.0:2888:3888;2181 server.3=192.168.100.203:2878:3878" \
  --replicas 1 \
  zookeeper:3.5
docker service create \
  --name zk3 \
  --network core-overlay \
  --publish mode=host,published=2171,target=2181 \
  --publish mode=host,published=2878,target=2888 \
  --publish mode=host,published=3878,target=3888 \
  --mount type=volume,source=zk-data,target=/data \
  --mount type=volume,source=zk-datalog,target=/datalog \
  --mount type=volume,source=zk-logs,target=/logs \
  -e ZOO_MY_ID=3 \
  -e ZOO_SERVERS="server.1=192.168.100.220:2878:3878 server.2=192.168.100.189:2878:3878 server.3=0.0.0.0:2888:3888;2181" \
  --constraint node.labels.zknode==3 \
  --replicas 1 \
  zookeeper:3.5
