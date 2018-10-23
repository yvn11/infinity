#!/bin/bash

begin=10000
end=10010
i=$begin

while [ $i -lt $end ] ; do
  go run gossip_node.go -p $i -b $begin -e $end &
  i=$(($i+1))
done
