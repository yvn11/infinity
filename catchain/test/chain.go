package main

import (
  catchain "github.com/zex/catchain/core"
  "fmt"
)

func print_keys(keys [][]byte) {
  if keys == nil {
    return
  }

  for i, k := range keys {
    fmt.Println(i, k)
  }
}

func main() {
  chain := catchain.NewChain()
  defer chain.Close()

  last, err := chain.LastBlock()
  if last != nil {
    fmt.Printf("%x, err:%v\n", last.Hash(), err)
  }

  err = chain.AddRaw([]byte("today is a nice day"))
  fmt.Println("set", err)
  fmt.Println(chain.GetBlock(catchain.Hash([]byte("today is a nice day"))))

  err = chain.AddRaw([]byte("yet another perfect day"))
  fmt.Println("set", err)
  fmt.Println(chain.GetBlock(catchain.Hash([]byte("yet another perfect day"))))

  fmt.Println("length", chain.Length().String())
  keys, err := chain.ListBlockKeys()

  if err != nil {
    fmt.Println("list error: ", err)
  } else {
    print_keys(keys)
  }
}
