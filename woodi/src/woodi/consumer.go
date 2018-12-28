package main

import (
  "github.com/Shopify/sarama"
  "github.com/golang/glog"
  "os"
  "os/signal"
  "flag"
  "strings"
  "woodi/common"
)

func main() {
  flag.Parse()
  cfg := sarama.NewConfig()

  cfg.Version = woodi.KAFKA_VERSION
  cfg.Consumer.Return.Errors = true

  glog.Info("version: ", cfg.Version)
  brks := strings.Split(*woodi.Brokers, ",")
  glog.Info("brokers: ", brks)
  glog.Info("topics: ", woodi.TOPIC_IMSG)
  cons, err := sarama.NewConsumer(brks, nil)
  if err != nil {
    glog.Error("create consumer failed: ", err)
    return
  }
  /**
  defer func() {
    if err := cons.Close(); err != nil {
      glog.Error("failed to close consumer: ", err)
    }}()
  */
  sig := make(chan os.Signal, 1)
  signal.Notify(sig, os.Interrupt)

  partCons, err := cons.ConsumePartition(woodi.TOPIC_IMSG, 0, sarama.OffsetNewest)
  if err != nil {
    glog.Error("get partition consumer failed: ", err)
    return
  }

  var recv_nr int
  ConsumerLoop:
  for {
    select {
    case msg := <-partCons.Messages():
      if msg == nil { continue }
      recv_nr++;
      glog.Infof("[%d] %v %v:%v\n", recv_nr, msg.Timestamp, msg.Key, msg.Value)
    case <-sig:
      partCons.AsyncClose()
      glog.Info("consumer quit")
      break ConsumerLoop
    case r := <-partCons.Errors():
      if r != nil {
        glog.Error("err: ", r)
      }
    }
  }
}
