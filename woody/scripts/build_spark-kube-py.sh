#!/bin/bash

docker build . \
  -t zlynch/spark-kube-py:1.0
  -f /fedev-data/spark-2.4.0-bin-hadoop2.7/kubernetes/dockerfiles/spark/bindings/python/Dockerfile \
  --build-arg base_img=zlynch/spark:2.4.0 \
