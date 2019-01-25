#!/bin/bash

 echo "`head -c 16 /dev/urandom | od -An -t x | tr -d ' '`,kubelet-bootstrap,10001,\"system:bootstrappers\"" > /etc/kubernetes/token
