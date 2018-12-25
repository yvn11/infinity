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
  cfg.Producer.Return.Successes = true
  fmt.Println("version: ", cfg.Version)

  pro, err := sarama.NewAsyncProducer(woodi.BROKERS, cfg)
  if err != nil {
    fmt.Println("create producer failed: ", err)
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
    }
    if sent_nr > 10 { break }
    select {
    case pro.Input() <-msg:
      fmt.Printf("sent[%d]: %v\n", sent_nr, msg)
      sent_nr++
    case <-sig:
      pro.AsyncClose()
      fmt.Println("producer quit")
      break
    case r := <-pro.Successes():
      fmt.Println("ok: ", r)
    case r := <-pro.Errors():
      fmt.Println("err: ", r)
    }
  }
}
