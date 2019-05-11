#!/bin/bash

hosts="
10.1.10.9
"

TOKEN=8aq3m7.dv0kahn9m5xd5tbh
CA_CERT=sha256:0d14513216d6b759f0f0916ba2b6694034978947fbb0da9884331368579c8e48
MASTER_ADDR=10.1.10.30:6443

for h in $hosts; do
  echo "$h"
  ssh $h "yes|kubeadm reset && systemctl stop kubelet && rm -rf /etc/kubernetes/pki /etc/kubernetes/*.conf /var/lib/kubelet/* && kubeadm join $MASTER_ADDR --node-name $h --token $TOKEN --discovery-token-ca-cert-hash $CA_CERT --ignore-preflight-errors SystemVerification,Swap -v 256"
done
