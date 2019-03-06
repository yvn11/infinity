#!/bin/bash

CASSANDRA_SERVERS=192.168.70.220,192.168.70.35,192.168.70.203
CASSANDRA_USER=dev
CASSANDRA_PASS=dcb5c69fedb78e9a29a3

./build/apiserver \
    -alsologtostderr \
    -cass $CASSANDRA_SERVERS \
    -cass_port 17001 \
    -apiaddr :17483 \
    -origins "http://192.168.70.140:*,http://woody_apiserver:*" \
    -cass_user $CASSANDRA_USER \
    -cass_pass $CASSANDRA_PASS
