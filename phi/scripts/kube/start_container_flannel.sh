#!/bin/bash

version=v0.10.0-amd64
image=quay.io/coreos/flannel:$version
container=flannel
MASTER_IP=10.1.10.30

docker rm -f $container
docker run -d \
  --name $container \
  --link etcd:etcd \
  --restart always \
  $image \
  "/opt/bin/flanneld -etcd-endpoints=http://etcd:2379,http://etcd:4001"
