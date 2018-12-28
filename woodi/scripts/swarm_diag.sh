#!/bin/bash

#--mount type=volume,source=diag-storage,target=/opt/diag/data \
docker service create \
  --name diag \
  --publish mode=host,published=17321,target=17321 \
  --mount type=volume,source=diag-storage,target=/opt/diag/data \
  --env-file /opt/algsvr-diag/config/updater-env \
  --replicas 5 \
  192.168.100.94:17889/smart-life/algsvr/diag/3_x:3.2.0.87

