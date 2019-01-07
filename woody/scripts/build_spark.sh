#!/bin/bash

image_tag=2.4.0
image_name=zlynch/spark
image=$image_name:$image_tag

docker build -t $image -f Dockerfile.spark .
