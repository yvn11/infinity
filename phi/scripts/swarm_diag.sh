#!/bin/bash

#--mount type=volume,source=diag-storage,target=/opt/diag/data \
docker service create \
  --name diag \
  --publish mode=host,published=17321,target=17321 \
  --mount type=volume,source=diag-storage,target=/opt/diag/data \
  --env-file /opt/algsvr-diag/config/updater-env \
  --replicas 5 \
  10.1.10.8:17889/zlynch/diag/3_x:3.2.0.87

