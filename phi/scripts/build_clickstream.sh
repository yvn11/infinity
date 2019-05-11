#!/bin/bash

image_tag=1.1
image_name=zlynch/clickstream
image=$image_name:$image_tag

docker build -t $image -f Dockerfile.aggr --build-arg "sched_pool=clickstream" . && \
docker push $image
