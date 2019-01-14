#!/bin/bash

#MASTER_IP=
#MASTER_PORT=
#token=
#hash_val=
#kubeadm join \
#  --token $token \
#  $MASTER_IP:$MASTER_PORT \
#  --discovery-token-ca-cert-hash sha256:$hash_val

kubeadm token create --print-join-command
