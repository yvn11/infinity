#!/bin/bash

version=1.2.6
image=k8s.gcr.io/coredns:$version
container=coredns

docker rm -f $container
docker run -d \
  --name $container \
  -p 53:53 \
  -v /etc/Corefile:/Corefile \
  --restart always \
  $image
