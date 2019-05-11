#!/bin/bash

hosts="
10.1.10.9
10.1.10.8
10.1.10.5
10.1.10.7
10.1.10.6
"
op=$1
if [[ -z $op ]] ;then echo "operation not specified"; exit -1; fi

for h in $hosts; do
  echo "$h: $op"
  ssh $h "$op"
done
