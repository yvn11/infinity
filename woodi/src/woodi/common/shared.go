package woodi

import (
  "flag"
  "github.com/Shopify/sarama"
)

var (
  KAFKA_VERSION = sarama.V2_1_0_0
  TOPIC_IMSG = "user_imsg"
  Brokers = flag.String("brokers", "localhost:9092", "broker list splitted by ','")
)
