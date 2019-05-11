#!/bin/bash

PREFIX_MIRROR=docker.io/mirrorgooglecontainers
PREFIX_K8S=k8s.gcr.io

images_1_10="
$PREFIX_MIRROR/kube-apiserver-amd64:v1.10.10
$PREFIX_MIRROR/kube-controller-manager-amd64:v1.10.10
$PREFIX_MIRROR/etcd-amd64:3.1.12
$PREFIX_MIRROR/k8s-dns-dnsmasq-nanny-amd64:1.14.8
$PREFIX_MIRROR/k8s-dns-kube-dns-amd64:1.14.8
$PREFIX_MIRROR/pause-amd64:3.1
"

#PREFIX_MIRROR=quay.io/zlynch

images_1_12="
$PREFIX_MIRROR/etcd:3.2.24
$PREFIX_MIRROR/kube-apiserver:v1.12.2
$PREFIX_MIRROR/kube-scheduler:v1.12.2
$PREFIX_MIRROR/kube-proxy:v1.12.2
$PREFIX_MIRROR/kube-controller-manager:v1.12.2
$PREFIX_MIRROR/coredns:1.2.2
$PREFIX_MIRROR/pause:3.1
"
#docker.io/coredns/coredns:1.2.2
#coredns/coredns:1.2.6
#$PREFIX_MIRROR/etcd:3.2.24
#$PREFIX_MIRROR/kube-apiserver:v1.13.2
#$PREFIX_MIRROR/kube-scheduler:v1.13.2
#$PREFIX_MIRROR/kube-proxy:v1.13.2
#$PREFIX_MIRROR/kube-controller-manager:v1.13.2
#$PREFIX_MIRROR/pause:3.1
images_1_13="
coredns/coredns:1.2.6
$PREFIX_MIRROR/etcd:3.2.24
$PREFIX_MIRROR/kube-apiserver:v1.13.2
$PREFIX_MIRROR/kube-scheduler:v1.13.2
$PREFIX_MIRROR/kube-proxy:v1.13.2
$PREFIX_MIRROR/kube-controller-manager:v1.13.2
$PREFIX_MIRROR/pause:3.1
"

for i in ${images_1_13} ;do
  docker pull $i
  docker tag $i $PREFIX_K8S/$(basename $i)
  docker rmi $i
#  docker tag $PREFIX_K8S/$(basename $i) 10.1.10.8:17889/$PREFIX_K8S/$(basename $i)
#  docker push 10.1.10.8:17889/$PREFIX_K8S/$(basename $i)
done
