#!/bin/bash

kubectl create -f - <<EOF
apiVersion: v1
kind: ServiceAccount
metadata:
  name: grpc-robot
EOF
