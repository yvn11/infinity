#!/bin/bash

hosts="
10.1.10.9
10.1.10.8
10.1.10.5
10.1.10.7
10.1.10.6
"
src=$1
dest=$2

if [[ -z $src ]] ;then echo "source not given"; exit -1; fi
if [[ -z $dest ]] ;then echo "destination not given"; exit -1; fi

for h in $hosts; do
  echo "$src => $h:$dest"
  rsync -a $src $h:$dest
done
