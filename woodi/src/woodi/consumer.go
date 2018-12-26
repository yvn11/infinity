package main

import (
  "github.com/Shopify/sarama"
  "fmt"
  "os"
  "os/signal"
  "woodi/common"
)

func main() {
  cfg := sarama.NewConfig()
  cfg.Consumer.Return.Errors = true
  ver, err := sarama.ParseKafkaVersion("2.1.0")
  if err != nil {
    fmt.Print("failed to parse kafka version", err)
    return
  }

  cfg.Version = ver

  fmt.Println("version: ", cfg.Version)
  cons, err := sarama.NewConsumer(woodi.BROKERS, nil)
  if err != nil {
    fmt.Println("create consumer failed: ", err)
    return
  }
  defer cons.Close()

  sig := make(chan os.Signal, 1)
  signal.Notify(sig, os.Interrupt)

  partCons, err := cons.ConsumePartition(woodi.TOPIC_IMSG, 0, sarama.OffsetNewest)
  if err != nil {
    fmt.Println("get partition consumer failed: ", err)
    return
  }
  defer partCons.Close()

  var recv_nr int

  for {
    select {
    case msg := <-partCons.Messages():
      recv_nr++;
      fmt.Printf("got[%d]: %v", recv_nr, msg)
    case <-sig:
      partCons.AsyncClose()
      fmt.Println("consumer quit")
      break
    case r := <-partCons.Errors():
      fmt.Println("err: ", r)
    }
  }
}
