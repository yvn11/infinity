package api

import (
  "strings"
  cql "github.com/gocql/gocql"
  "github.com/golang/glog"
  "woody/common"
)

func CassSession(keyspace string) (*cql.Session) {
  srv := strings.Split(*woody.CassCluster, ",")
  glog.Infof("cass cluster: %v:%d apiserver: %v", srv, *woody.CassPort, *woody.ApiAddr)
  if len(srv) == 0 { glog.Fatal("cassandra cluster not given") }

  cass_conf := cql.NewCluster()
  cass_conf.Hosts = srv
  cass_conf.CQLVersion = *woody.CQLVersion
  cass_conf.Keyspace = keyspace
  cass_conf.Port = *woody.CassPort
  cass_conf.IgnorePeerAddr = true
  cass_conf.Consistency = cql.One
  cass_conf.Authenticator = cql.PasswordAuthenticator{
    Username: *woody.CassUser,
    Password: *woody.CassPass,
  }

  cass_sess, err := cass_conf.CreateSession()
  if err != nil {
    glog.Fatal("failed to create cassandra session: ", err)
  }

  return cass_sess
}
