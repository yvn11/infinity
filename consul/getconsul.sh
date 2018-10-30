#!/bin/bash

targt=https://releases.hashicorp.com/consul/1.3.0/consul_1.3.0_linux_amd64.zip
output=consul_1.3.0_linux_amd64.zip

curl -o $output $target
unzip $output
