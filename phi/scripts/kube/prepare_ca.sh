#!/bin/bash

MASTER_IP=192.168.0.102
MASTER_CLUSTER_IP=192.168.0.102

if [[ ! -f easy-rsa.tar.gz ]] ;then
  curl -LO https://storage.googleapis.com/kubernetes-release/easy-rsa/easy-rsa.tar.gz
fi
tar xf easy-rsa.tar.gz
cd easy-rsa-master/easyrsa3
EASYRSA=./easyrsa

echo yes|$EASYRSA init-pki
$EASYRSA --batch "--req-cn=${MASTER_IP}@`date +%s`" build-ca nopass
$EASYRSA --subject-alt-name="IP:${MASTER_IP},"\
"IP:${MASTER_CLUSTER_IP},"\
"DNS:kubernetes,"\
"DNS:kubernetes.default,"\
"DNS:kubernetes.default.svc,"\
"DNS:kubernetes.default.svc.cluster,"\
"DNS:kubernetes.default.svc.cluster.local" \
--days=10000 \
build-server-full server nopass

KEY_ROOT=/etc/kubernetes/keys
mkdir -p $KEY_ROOT
cp pki/ca.crt pki/issued/server.crt pki/private/server.key $KEY_ROOT
chmod +r $KEY_ROOT/*
#--client-ca-file=/yourdirectory/ca.crt
#--tls-cert-file=/yourdirectory/server.crt
#--tls-private-key-file=/yourdirectory/server.key
