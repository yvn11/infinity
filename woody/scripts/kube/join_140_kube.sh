#!/bin/bash

TOKEN=pcoda9.4keet38l0bz9c5sg
CA_HASH=sha256:e85aba24ebd2abd22539dd33df2cceefe0f7b8e0fba5266dad5036fd512937ef

kubeadm join 192.168.70.140:6443 \
  --token $TOKEN \
  --discovery-token-ca-cert-hash $CA_HASH
