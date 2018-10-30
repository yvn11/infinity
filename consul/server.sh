#!/bin/bash
self="$(ip addr show dev eno1|awk '$1 == "inet"{sub("/.*","",$2);print$2}')"

if [[ -z $self ]] ;then 
  self="$(ip addr show dev `ip addr show |awk -F: '{print $2}'|sed -e 's/ //g'|grep enp`|awk '$1 == "inet"{sub("/.*","",$2);print$2}')"
fi

./consul agent \
  -server \
  -bind $self \
  -node `uuidgen` \
  -data-dir /algsvr/consul
