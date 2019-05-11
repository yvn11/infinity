#!/bin/bash

version=v1.13.2
image=k8s.gcr.io/kube-scheduler:$version
container=kube-scheduler

docker rm -f $container
docker run -d \
  --name $container \
  -p 10348:10348 \
  --link kube-apiserver:kube-apiserver \
  -v /etc/kubernetes:/etc/kubernetes \
  --restart always \
  $image \
  kube-scheduler --logtostderr=true --v=256 --master=http://kube-apiserver:8080 \
    --address 0.0.0.0 --port 10348 \
    --kubeconfig=/etc/kubernetes/scheduler.conf \
    --leader-elect=true
