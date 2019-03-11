#!/bin/bash
# run in spark-2.4.0-bin-hadoop2.7 root
spark_base=zlynch/spark-kube:2.4
spark_py=zlynch/spark-kube-py:1.0

function build_spark_base() {
  docker build \
    -f kubernetes/dockerfiles/spark/Dockerfile \
    -t $spark_base . && \
  docker push $spark_base
}

function build_spark_py() {
  docker build \
    -f kubernetes/dockerfiles/spark/bindings/python/Dockerfile \
    -t $spark_py \
    --build-arg base_img=$spark_base . && \
  docker push $spark_py
}

build_spark_base && \
build_spark_py
