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
    spark_sched_mode = environ.get("SPARK_SCHED_MODE", "FAIR")
    spark_sched_pool = environ.get("SPARK_SCHED_POOL", "dev")
    spark_sched_file = environ.get("SPARK_SCHED_FILE", "/opt/spark/conf/fairscheduler.xml")
