#!/bin/bash

ADDR=10.1.10.30
PORT=8001

curl http://$ADDR:$PORT/api/v1/namespaces/kube-system/services/https:kubernetes-dashboard:/proxy

