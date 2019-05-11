#!/bin/bash

iptables -I INPUT -i em1 -p tcp --dport 8001 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 4040 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 10251 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 10000 -m state --state NEW,ESTABLISHED -j ACCEPT

iptables -I INPUT -i em1 -p tcp --dport 8500 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 8300 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 8600 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 8301 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 8302 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 2377 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 4789 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -I INPUT -i em1 -p tcp --dport 7946 -m state --state NEW,ESTABLISHED -j ACCEPT
