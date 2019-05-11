#!/bin/bash

iptables -A INPUT -s 172.17.0.0/16 -i docker0 -p tcp -j ACCEPT

