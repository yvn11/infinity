#!/bin/bash

version=v1.10.0
image=k8s.gcr.io/kubernetes-dashboard-amd64:$version
container=kube-dashboard
MASTER_IP=192.168.70.140
MASTER_PORT=8080

docker rm -f $container
docker run -it \
  --name $container \
  -p 9090:9090 \
  --link kube-apiserver:kube-apiserver \
  -v /etc/kubernetes:/etc/kubernetes \
  -e KUBERNETES_SERVICE_HOST=kube-apiserver \
  -e KUBERNETES_SERVICE_PORT=$MASTER_PORT \
  --restart always \
  $image
