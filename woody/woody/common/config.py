from os import environ

class Config:
    cassandra_servers = environ.get("CASSANDRA_SERVERS", "").split(",")
    cassandra_port = int(environ.get("CASSANDRA_PORT", "9042"))
    cassandra_user = environ.get("CASSANDRA_USER", "")
    cassandra_pass = environ.get("CASSANDRA_PASS", "")
    kafka_brokers = environ.get("KAFKA_BROKERS", "")
    zoo_servers = environ.get("ZOO_SERVERS", "")
    ssc_duration = int(environ.get("SSC_DURATION", "1")) # batch duration in second
    spark_master = environ.get("SPARK_MASTER", "local")
