#!/bin/bash

hosts="
192.168.70.35
192.168.70.94
192.168.70.220
192.168.70.203
192.168.70.189
"
src=$1
dest=$2

if [[ -z $src ]] ;then echo "source not given"; exit -1; fi
if [[ -z $dest ]] ;then echo "destination not given"; exit -1; fi

for h in $hosts; do
  echo "$src => $h:$dest"
  rsync -a $src $h:$dest
done
