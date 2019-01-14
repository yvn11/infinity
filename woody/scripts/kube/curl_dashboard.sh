#!/bin/bash

ADDR=192.168.70.140
PORT=8001

curl http://$ADDR:$PORT/api/v1/namespaces/kube-system/services/https:kubernetes-dashboard:/proxy

