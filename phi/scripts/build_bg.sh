#!/bin/bash

image_tag=1.1
image_name=zlynch/phi-bg
image=$image_name:$image_tag

docker build -t $image -f "Dockerfile.bg" . && \
docker push $image
