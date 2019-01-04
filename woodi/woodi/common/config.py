from os import environ

class Config:
    cassandra_servers = environ.get("CASSANDRA_SERVERS", "").split(",")
    cassandra_port = int(environ.get("CASSANDRA_PORT", "9042"))
    cassandra_user = environ.get("CASSANDRA_USER", "")
    cassandra_pass = environ.get("CASSANDRA_PASS", "")
