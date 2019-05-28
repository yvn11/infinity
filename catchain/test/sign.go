package main

import (
  "fmt"
  "github.com/zex/catchain/sign"
)

func main() {
  a := sign.Algorithm{}
  pri := a.PrivateKey()
  pub := a.PublicKey(pri)
  msg := []byte("let's meet at 10 PM")
  signed := a.Sign(pri, msg)
  valid := a.Verify(pub, msg, signed)

  fmt.Println("pri", pri)
  fmt.Println("pub", pub)
  fmt.Println("signed", signed)
  fmt.Println("valid", valid)
}
