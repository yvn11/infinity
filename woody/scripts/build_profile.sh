#!/bin/bash

image_tag=1.1
image_name=zlynch/woody-aggr
image=$image_name:$image_tag

docker build -t $image -f Dockerfile.aggr --build-arg "sched_pool=userprofile" . && \
docker push $image
