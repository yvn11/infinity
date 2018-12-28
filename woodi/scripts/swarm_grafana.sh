#!/bin/bash

# TODO: ns lookup
# with IPs, servers must be configured manually on each node by setting self to 0.0.0.0

docker service create \
  --name grafana \
  --network core-overlay \
  --publish mode=host,published=13000,target=3000 \
  --constraint node.hostname==core.master \
  --replicas 1 \
  grafana/grafana:5.2.0
