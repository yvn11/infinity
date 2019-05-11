#!/bin/bash

kubectl create namespace istio-apps
kubectl label namespace istio-apps istio-injection=enabled
