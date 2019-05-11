#!/bin/bash

CASSANDRA_SERVERS=10.1.10.5,10.1.10.9,10.1.10.7
CASSANDRA_USER=dev
CASSANDRA_PASS=dcb5c69fedb78e9a29a3

./build/apiserver \
    -alsologtostderr \
    -cass $CASSANDRA_SERVERS \
    -cass_port 17001 \
    -apiaddr :17483 \
    -origins "http://10.1.10.30:*,http://phi_apiserver:*" \
    -cass_user $CASSANDRA_USER \
    -cass_pass $CASSANDRA_PASS
