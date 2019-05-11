#!/bin/bash

docker service create \
  --name diag-ui \
  --network core-overlay \
  --publish mode=host,published=17322,target=80 \
  --restart-condition any \
  --replicas 5 \
  10.1.10.8:17889/zlynch/diag-ui/3_x:3.2.0.87

