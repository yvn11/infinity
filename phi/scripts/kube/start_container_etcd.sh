#!/bin/bash

version=3.2.24
image=k8s.gcr.io/etcd:$version \
container=etcd

#  -p 2379:2379 \
#  -p 2380:2380 \
#  -p 4001:4001 \
docker rm -f $container
docker run -d \
  --name $container \
  -v /etc/kubernetes:/etc/kubernetes \
  -v /var/lib/etcd/default.etcd:/var/lib/etcd/default.etcd \
  --restart always \
  $image \
  /usr/local/bin/etcd --name=default --data-dir=//var/lib/etcd/default.etcd --listen-client-urls=http://0.0.0.0:2379 --advertise-client-urls=http://10.1.10.30:2379
