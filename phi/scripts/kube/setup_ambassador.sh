#!/bin/bash

# check RBAC support
#kubectl cluster-info dump --namespace kube-system | grep authorization-mode
kubectl apply -f https://getambassador.io/yaml/ambassador/ambassador-rbac.yaml
