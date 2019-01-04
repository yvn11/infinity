package main

import (
  "github.com/Shopify/sarama"
  "github.com/golang/glog"
  "os"
  "time"
  "os/signal"
  "woody/common"
  "flag"
  "strings"
)

func main() {
  flag.Parse()
  cfg := sarama.NewConfig()
  cfg.Version = woody.KAFKA_VERSION
  cfg.Producer.Return.Successes = true
  glog.Info("version: ", cfg.Version)

  brks := strings.Split(*woody.Brokers, ",")
  glog.Info("brokers: ", brks)
  glog.Info("topics: ", woody.TOPIC_IMSG)
  pro, err := sarama.NewAsyncProducer(brks, cfg)
  if err != nil {
    glog.Error("create producer failed: ", err)
    return
  }
  /**
  defer func() {
    if err := pro.Close(); err != nil {
      glog.Error("failed to close producer: ", err)
    }}()
  */
  sig := make(chan os.Signal, 1)
  signal.Notify(sig, os.Interrupt)

  var sent_nr int
  ProducerLoop:
  for {
    msg := &sarama.ProducerMessage{
      Topic: woody.TOPIC_IMSG,
      Value: sarama.StringEncoder(time.Now().String()),
      Timestamp: time.Now(),
    }
    //if sent_nr > 10 { break }
    select {
    case pro.Input() <-msg:
      glog.Infof("sent[%d]: %v\n", sent_nr, msg)
      sent_nr++
    case <-sig:
      pro.AsyncClose()
      glog.Info("producer quit")
      break ProducerLoop
    case r := <-pro.Successes():
      glog.Info("ok: ", r)
    case r := <-pro.Errors():
      glog.Info("err: ", r)
    }
  }
}
