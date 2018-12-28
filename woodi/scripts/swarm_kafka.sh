#!/bin/bash

# TODO: ns lookup
# with IPs, servers must be configured manually on each node by setting self to 0.0.0.0
#--env ZOO_SERVERS="server.1=192.168.100.203:2888:3888 server.2=192.168.100.189:2888:3888 server.3=192.168.100.220:2888:3888" \
#-e KAFKA_LISTENER_SECURITY_PROTOCOL_MAP: INSIDE:PLAINTEXT,OUTSIDE:PLAINTEXT
#-e KAFKA_INTER_BROKER_LISTENER_NAME=INSIDE
#--constraint node.hostname==core.master
#-e KAFKA_ADVERTISED_LISTENERS=INTERNAL://:17810,PUBLIC://:17811 \
#  -e KAFKA_LISTENER_SECURITY_PROTOCOL_MAP=INTERNAL:PLAINTEXT,PUBLIC:PLAINTEXT \
#  -e KAFKA_INTER_BROKER_LISTENER_NAME=INTERNAL \

docker service create \
  --name kafka \
  --network core-overlay \
  --mount type=volume,source=kfk-data,target=/kafka \
  --publish mode=host,published=17810,target=17810 \
  --publish mode=host,published=17812,target=17812 \
  -e KAFKA_BROKER_ID=-1 \
  -e KAFKA_PORT=17810 \
  -e KAFKA_CLEANUP_POLICY=compact \
  -e KAFKA_LISTENERS=PLAINTEXT://:12710 \
  -e KAFKA_ZOOKEEPER_CONNECT="192.168.100.203:2181,192.168.100.189:2181,192.168.100.220:2181" \
  --constraint node.hostname==core.master \
  --replicas 1 \
  wurstmeister/kafka:2.12-2.1.0
