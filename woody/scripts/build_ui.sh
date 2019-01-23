#!/bin/bash

image_tag=1.0
image_name=zlynch/woody-ui
image=$image_name:$image_tag

docker build -t $image -f Dockerfile.ui . && \
docker push $image
