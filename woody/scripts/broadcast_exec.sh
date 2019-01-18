#!/bin/bash

hosts="
192.168.70.35
192.168.70.94
192.168.70.220
192.168.70.203
192.168.70.189
"
op=$1
if [[ -z $op ]] ;then echo "operation not specified"; exit -1; fi

for h in $hosts; do
  echo "$h: $op"
  ssh $h "$op"
done
