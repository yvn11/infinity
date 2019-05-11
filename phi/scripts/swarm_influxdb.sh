#!/bin/bash

# TODO: ns lookup
# with IPs, servers must be configured manually on each node by setting self to 0.0.0.0

docker service create \
  --name influxdb \
  --network core-overlay \
  --publish mode=host,published=13001,target=8086 \
  --constraint node.hostname==core.master \
  --mount type=volume,source=influxdb-data,target=/var/lib/influxdb \
  --replicas 1 \
  docker.io/influxdb:alpine
