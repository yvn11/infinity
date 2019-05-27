package main

import (
  "github.com/zex/catchain/store"
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
  s := store.NewStore()
  defer s.Close()

  fmt.Println("get [zex]", s.Get([]byte("zex")))
  fmt.Println(s.Has([]byte("Pikachu")))
  keys, err := s.ListKeys(nil)

  if err != nil {
    fmt.Println("list error: ", err)
  } else {
    print_keys(keys)
  }
}
