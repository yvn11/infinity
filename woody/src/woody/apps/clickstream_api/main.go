package main

import (
  "flag"
  "woody/api"
)

func main() {
  flag.Parse()
  app := api.NewClickstreamApi()
  app.Start()
}
