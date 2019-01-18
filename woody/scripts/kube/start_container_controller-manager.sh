#!/bin/bash

version=v1.12.2
image=k8s.gcr.io/kube-controller-manager:$version
container=kube-controller-manager

docker rm -f $container
docker run -d \
  --name $container \
  -p 10250:10250 \
  --link kube-apiserver:kube-apiserver \
  -v /etc/kubernetes:/etc/kubernetes \
  --restart always \
  $image \
  kube-controller-manager --logtostderr=true --v=256 --master=http://kube-apiserver:8080 \
 --allocate-node-cidrs=true \
 --authentication-kubeconfig=/etc/kubernetes/controller-manager.conf \
 --authorization-kubeconfig=/etc/kubernetes/controller-manager.conf\
 --client-ca-file=/etc/kubernetes/pki/ca.crt\
 --cluster-cidr=10.1.0.0/16\
 --cluster-signing-cert-file=/etc/kubernetes/pki/ca.crt\
 --cluster-signing-key-file=/etc/kubernetes/pki/ca.key\
 --controllers=*,bootstrapsigner,tokencleaner\
 --kubeconfig=/etc/kubernetes/controller-manager.conf\
 --leader-elect=true\
 --node-cidr-mask-size=24\
 --requestheader-client-ca-file=/etc/kubernetes/pki/front-proxy-ca.crt\
 --root-ca-file=/etc/kubernetes/pki/ca.crt\
 --service-account-private-key-file=/etc/kubernetes/pki/sa.key\
 --use-service-account-credentials=true
