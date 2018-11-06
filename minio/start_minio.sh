#!/bin/bash

tag=RELEASE.2018-11-06T01-01-02Z
img=docker.io/minio/minio:$tag
cont=minio

docker rm -f $cont
docker run -it \
  --restart always \
  --name $cont \
  -v `pwd`/minio-data:/data:z \
  -e MINIO_HTTP_TRACE=/data/minio.log \
  -e MINIO_ACCESS_KEY=admin \
  -e MINIO_SECRET_KEY=c7ba9d0b277c \
  -p 17870:9000 \
  $img \
  server /data

