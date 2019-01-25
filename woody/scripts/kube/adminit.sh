#!/bin/bash

#swapoff -a
#swapon
#./kubernetes/server/bin/

#--apiserver-advertise-address=192.168.70.140 \
#--ignore-preflight-errors=all \
#--cri-socket /var/run/crio/crio.sock \
kubeadm init \
    --kubernetes-version 1.13.2 \
    --node-name 192.168.70.140 \
    --pod-network-cidr=10.244.0.0/16 \
    --service-cidr=10.244.10.0/16 \
    -v 256 \
    --ignore-preflight-errors SystemVerification,DirAvailable--var-lib-etcd,\
FileAvailable--etc-kubernetes-manifests-kube-apiserver.yaml,\
FileAvailable--etc-kubernetes-manifests-kube-controller-manager.yaml,\
FileAvailable--etc-kubernetes-manifests-kube-scheduler.yaml,\
FileAvailable--etc-kubernetes-manifests-etcd.yaml,\
Port-6443,\
Port-10250,\
Port-2379,\
Port-10252,\
Port-2380,\
Port-10251

if [[ -f /etc/kubernetes/admin.conf ]] ;then
  cp /etc/kubernetes/admin.conf ~/.kube/config
fi
