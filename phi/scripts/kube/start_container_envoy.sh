#!/bin/bash

image=envoyproxy/envoy:latest
image=envoy-grpc:1.0

if [[ $1 -eq 1 ]] ;then
docker rm -f envoy
docker run \
  -d \
  --restart always \
  --name envoy \
  --privileged=true \
  --net bridge \
  --link server-1784:server-1784 \
  --link server-1785:server-1785 \
  -v `pwd`/kube/etc-envoy-envoy.yaml:/etc/envoy/envoy.yaml \
  -p 14390:14390 \
  -p 9901:9901 \
  $image \
  /usr/local/bin/envoy -l trace --v2-config-only -c /etc/envoy/envoy.yaml
else
  docker restart envoy
fi
