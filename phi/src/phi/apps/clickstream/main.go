package main

import (
  "flag"
  "phi/producers"
)

func main() {
  flag.Parse()
  pro := producers.NewClickstreamProducer()
  pro.Run()
}
