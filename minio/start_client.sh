#!/bin/bash

tag=RELEASE.2018-11-06T01-12-20Z
img=docker.io/minio/mc:$tag
cont=minio-cli

docker rm -f $cont
docker run -it \
  --link minio \
  --network bridge \
  --name $cont \
  $img $@

# config host add minio http://localhost:17870 admin c7ba9d0b277c
 
