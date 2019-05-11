#!/bin/bash

#swapoff -a
#swapon
#./kubernetes/server/bin/

#--apiserver-advertise-address=10.1.10.30 \
#--ignore-preflight-errors=all \
#--cri-socket /var/run/crio/crio.sock \
kubeadm init \
    --kubernetes-version 1.13.2 \
    --node-name 10.1.10.30 \
    --pod-network-cidr=10.244.0.0/16 \
    --service-cidr=10.244.0.0/16 \
    -v 256 \
    --ignore-preflight-errors SystemVerification,DirAvailable--var-lib-etcd

if [[ -f /etc/kubernetes/admin.conf ]] ;then
  cp /etc/kubernetes/admin.conf ~/.kube/config
fi
