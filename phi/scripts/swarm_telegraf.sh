#!/bin/bash

# TODO: ns lookup
# with IPs, servers must be configured manually on each node by setting self to 0.0.0.0

docker service create \
  --name telegraf \
  --network core-overlay \
  --publish mode=host,published=13002,target=8092,protocol=udp \
  --publish mode=host,published=13003,target=8094 \
  --publish mode=host,published=13004,target=8125,protocol=udp \
  --mount type=bind,source=/telegraf/telegraf.conf,target=/etc/telegraf/telegraf.conf \
  --mount type=bind,source=/proc,target=/host/proc,readonly \
  --mount type=bind,source=/var/run/utmp,target=/var/run/utmp,readonly \
  --mount type=bind,source=/var/run/docker.sock,target=/var/run/docker.sock,readonly \
  --mount type=volume,source=telegraf-data,target=/var/lib/telegraf \
  --mount type=bind,source=/tmp,target=/tmp \
  --hostname '{{.Node.Hostname}}' \
  -e HOST_PROC=/host/proc \
  --mode global \
  docker.io/telegraf:alpine
