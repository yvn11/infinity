#!/bin/bash

PREFIX_MIRRO=docker.io/mirrorgooglecontainers
PREFIX_K8S=k8s.gcr.io

images_1_10="
$PREFIX_MIRRO/kube-apiserver-amd64:v1.10.10
$PREFIX_MIRRO/kube-controller-manager-amd64:v1.10.10
$PREFIX_MIRRO/etcd-amd64:3.1.12
$PREFIX_MIRRO/k8s-dns-dnsmasq-nanny-amd64:1.14.8
$PREFIX_MIRRO/k8s-dns-kube-dns-amd64:1.14.8
$PREFIX_MIRRO/pause-amd64:3.1
"

PREFIX_MIRRO=quay.io/zlynch

images_1_12="
$PREFIX_MIRRO/etcd:3.2.24
$PREFIX_MIRRO/kube-apiserver:v1.12.2
$PREFIX_MIRRO/kube-scheduler:v1.12.2
$PREFIX_MIRRO/kube-proxy:v1.12.2
$PREFIX_MIRRO/kube-controller-manager:v1.12.2
$PREFIX_MIRRO/coredns:1.2.2
$PREFIX_MIRRO/pause:3.1
"
#docker.io/coredns/coredns:1.2.2

for i in ${images_1_12} ;do
  docker pull $i
  docker tag $i $PREFIX_K8S/$(basename $i)
  docker rmi $i
#  docker tag $PREFIX_K8S/$(basename $i) 192.168.70.94:17889/$PREFIX_K8S/$(basename $i)
#  docker push 192.168.70.94:17889/$PREFIX_K8S/$(basename $i)
done
