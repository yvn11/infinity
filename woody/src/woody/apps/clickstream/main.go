package main

import (
  "flag"
  "woody/producers"
)

func main() {
  flag.Parse()
  pro := producers.NewClickstreamProducer()
  pro.Run()
}
