package config

import "os"

const (
  VERSION = "0.0.1"
  APP_NAME = "Truth"
)

var (
  RPC_PUBLIC_PORT = os.Getenv("RPC_PUBLIC_PORT")
  RPC_MNG_PORT = os.Getenv("RPC_MNG_PORT")
  REST_PUBLIC_PORT = os.Getenv("REST_PUBLIC_PORT")
)
