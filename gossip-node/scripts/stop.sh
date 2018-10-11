#!/bin/bash

for i in `ps a|grep "exe/gossip-node"|grep -v "grep"|awk '{print$1}'` ;do kill $i; done
