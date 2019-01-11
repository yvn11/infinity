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
  TOPIC_PROFILE = "profile"
  Brokers = flag.String("brokers", "localhost:9092", "broker list splitted by ','")
)
