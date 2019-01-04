#!/bin/bash

docker service create \
  --name diag-ui \
  --network core-overlay \
  --publish mode=host,published=17322,target=80 \
  --restart-condition any \
  --replicas 5 \
  192.168.100.94:17889/smart-life/algsvr/diag-ui/3_x:3.2.0.87

