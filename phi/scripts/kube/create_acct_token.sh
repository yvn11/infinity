#!/bin/bash

kubectl create -f - <<EOF
apiVersion: v1
kind: Secret
metadata:
  name: grpc-robot-secret
  annotations:
    kubernetes.io/service-account.name: grpc-robot
type: kubernetes.io/service-account-token
EOF
