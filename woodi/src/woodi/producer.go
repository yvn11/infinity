package main

import (
  "github.com/Shopify/sarama"
  "github.com/golang/glog"
  "os"
  "time"
  "os/signal"
  "woodi/common"
  "flag"
  "strings"
)

func main() {
  flag.Parse()
  cfg := sarama.NewConfig()
  cfg.Version = woodi.KAFKA_VERSION
  cfg.Producer.Return.Successes = true
  glog.Info("version: ", cfg.Version)

  brks := strings.Split(*woodi.Brokers, ",")
  glog.Info("brokers: ", brks)
  pro, err := sarama.NewAsyncProducer(brks, cfg)
  if err != nil {
    glog.Error("create producer failed: ", err)
    return
  }
  defer pro.Close()

  sig := make(chan os.Signal, 1)
  signal.Notify(sig, os.Interrupt)

  var sent_nr int

  for {
    msg := &sarama.ProducerMessage{
      Topic: woodi.TOPIC_IMSG,
      Value: sarama.StringEncoder("today "),
      Timestamp: time.Now(),
    }
    if sent_nr > 10 { break }
    select {
    case pro.Input() <-msg:
      glog.Infof("sent[%d]: %v\n", sent_nr, msg)
      sent_nr++
    case <-sig:
      pro.AsyncClose()
      glog.Info("producer quit")
      break
    case r := <-pro.Successes():
      glog.Info("ok: ", r)
    case r := <-pro.Errors():
      glog.Info("err: ", r)
    }
  }
}
