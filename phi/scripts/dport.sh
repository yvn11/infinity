#!/bin/bash

if [[ -z $1 ]] ;then echo "port not specified"; exit -1; fi

iptables -I INPUT -i em1 -p tcp --dport $1 -m state --state NEW,ESTABLISHED -j ACCEPT
