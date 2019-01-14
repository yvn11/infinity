#!/bin/bash

image_tag=1.0
image_name=zlynch/click-stream
image=$image_name:$image_tag

docker build -t $image -f Dockerfile.clickstream . && \
docker push $image