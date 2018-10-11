#!/bin/bash

begin=10000
end=11000
i=$begin

while [ $i -lt $end ] ; do
  go run gossip_node.go -p $i -b $begin -e $end &
  i=$(($i+1))
done
