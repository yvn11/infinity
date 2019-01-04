#!/bin/bash

super_u=cassandra
super_p=cassandra

dev_pass=`uuidgen |awk -F- '{print $1$5}'`
echo cqlsh -C -u $super_u -p $super_p -e "CREATE USER IF NOT EXISTS dev WITH PASSWORD '$dev_pass' NOSUPERUSER;GRANT MODIFY ON ALL KEYSPACES TO dev;"
cat > .dev_pass << EOF
$dev_pass
EOF

readonly_pass=`uuidgen |awk -F- '{print $1$5}'`
echo cqlsh -C -u $super_u -p $super_p -e "CREATE USER IF NOT EXISTS readonly WITH PASSWORD '$readonly_pass' NOSUPERUSER;GRANT MODIFY ON ALL KEYSPACES TO readonly;"
cat > .readonly_pass << EOF
$readonly_pass
EOF
