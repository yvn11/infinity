package main

import (
  catchain "github.com/zex/catchain/core"
  "fmt"
)

func main() {
  chain := catchain.NewChain()
  fmt.Printf("%x\n", chain.LastBlock().Hash())

  chain.AddRaw([]byte("today is a nice day"))
  fmt.Printf("%x\n", chain.LastBlock().Hash())

  chain.AddRaw([]byte("yet another perfect day"))
  fmt.Printf("%x\n", chain.LastBlock().Hash())
}
