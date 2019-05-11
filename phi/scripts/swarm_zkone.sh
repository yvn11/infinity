#!/bin/bash

# TODO: ns lookup
# with IPs, servers must be configured manually on each node by setting self to 0.0.0.0
#--env ZOO_SERVERS="server.1=10.1.10.7:2888:3888 server.2=10.1.10.6:2888:3888 server.3=10.1.10.5:2888:3888" \

docker service create \
  --name zk \
  --network core-overlay \
  --publish mode=host,published=2171,target=2181 \
  --publish mode=host,published=2878,target=2888 \
  --publish mode=host,published=3878,target=3888 \
  --mount type=volume,source=zk-data,target=/data \
  --mount type=volume,source=zk-datalog,target=/datalog \
  --mount type=volume,source=zk-logs,target=/logs \
  --mount type=bind,source=/zk-conf,target=/conf \
  --constraint node.labels.zknode_enable==true \
  --replicas 3 \
  zookeeper:3.5
