#!/bin/bash
set -ex

MASTER_IP=192.168.0.102
MASTER_CLUSTER_IP=192.168.0.102

OUTPUT_ROOT=kube
openssl genrsa -out $OUTPUT_ROOT/ca.key 2048
openssl req -x509 -new -nodes -key $OUTPUT_ROOT/ca.key -subj "/CN=${MASTER_IP}" -days 10000 -out $OUTPUT_ROOT/ca.crt
openssl genrsa -out $OUTPUT_ROOT/server.key 2048
openssl req -new -key $OUTPUT_ROOT/server.key -out $OUTPUT_ROOT/server.csr -config kube/csr.conf
openssl x509 -req -in $OUTPUT_ROOT/server.csr -CA $OUTPUT_ROOT/ca.crt -CAkey $OUTPUT_ROOT/ca.key \
  -CAcreateserial -out $OUTPUT_ROOT/server.crt -days 10000 \
  -extensions v3_ext -extfile kube/csr.conf
openssl x509 -noout -text -in $OUTPUT_ROOT/server.crt
KEY_DEST=/etc/kubernetes/keys
cp $OUTPUT_ROOT/ca.crt $OUTPUT_ROOT/server.crt $OUTPUT_ROOT/server.key $KEY_DEST

