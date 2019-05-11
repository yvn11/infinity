#!/bin/bash

docker exec -i docker-registry /bin/sh -c 'registry garbage-collect /etc/docker/registry/config.yml' &> /tmp/registry_gc.log
