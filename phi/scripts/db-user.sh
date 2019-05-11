#!/bin/bash

super_u=
super_p=
host=
port=

dev_pass=`uuidgen |awk -F- '{print $1$5}'`
cqlsh -C -u $super_u -p $super_p -e "CREATE USER IF NOT EXISTS dev WITH PASSWORD '$dev_pass' NOSUPERUSER;
GRANT MODIFY ON ALL KEYSPACES TO dev;
GRANT CREATE ON ALL KEYSPACES TO dev;
GRANT DROP ON ALL KEYSPACES TO dev;
GRANT ALTER ON ALL KEYSPACES TO dev;
GRANT SELECT ON ALL KEYSPACES TO dev;" $host $port
cat > .dev_pass << EOF
$dev_pass
EOF

readonly_pass=`uuidgen |awk -F- '{print $1$5}'`
cqlsh -C -u $super_u -p $super_p -e "CREATE USER IF NOT EXISTS readonly WITH PASSWORD '$readonly_pass' NOSUPERUSER;
GRANT SELECT ON ALL KEYSPACES TO readonly;" $host $port
cat > .readonly_pass << EOF
$readonly_pass
EOF
