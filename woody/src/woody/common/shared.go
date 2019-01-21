package woody

import (
  "flag"
  "github.com/Shopify/sarama"
)

var (
  KAFKA_VERSION = sarama.V2_1_0_0
  TOPIC_IMSG = "user_imsg"
  TOPIC_CLICK = "click_ev"
  TOPIC_BUY = "buy_ev"
  TOPIC_PROFILE = "profile" // TBD(zex)
  Brokers = flag.String("brokers", "localhost:9092", "broker list, splitted by ','")
  CassCluster = flag.String("cass", "localhost", "cassandra server address, splitted by ','")
  CassPort = flag.Int("cass_port", 9042, "cassandra server port")
  CassUser = flag.String("cass_user", "", "cassandra server user")
  CassPass = flag.String("cass_pass", "", "cassandra server password")
  CQLVersion = flag.String("cqlversion", "3.4.4", "CQL version string")
  ApiAddr = flag.String("apiaddr", ":12345", "backend bind address")
  Origins = flag.String("origins", "localhost", "origins splitted by ','")
)
