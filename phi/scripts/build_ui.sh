#!/bin/bash

image_tag=1.1
image_name=zlynch/phi-ui
image=$image_name:$image_tag

docker build -t $image -f Dockerfile.ui --build-arg "PRODUCTION=--prod" . && \
docker push $image
