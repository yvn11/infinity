#!/bin/bash

version=v1.12.2
image=k8s.gcr.io/kube-proxy:$version
container=kube-proxy

MASTER_IP=10.1.10.30
MASTER_PORT=8080

docker rm -f $container
docker run -d \
  --name $container \
  --link kube-apiserver:kube-apiserver \
  -p 10249:10249 \
  -e KUBERNETES_SERVICE_HOST=$MASTER_IP \
  -e KUBERNETES_SERVICE_PORT=$MASTER_PORT \
  -v /etc/kubernetes:/etc/kubernetes \
  --privileged=true \
  --restart always \
  $image \
  kube-proxy --logtostderr=true --v=256 --master=kube-apiserver:$MASTER_PORT
