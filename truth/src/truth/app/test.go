package main

import (
  "os"
  "flag"
  "github.com/golang/glog"
  elli "crypto/elliptic"
  ecdsa "crypto/ecdsa"
)

func main() {
  flag.Parse()
  glog.Info("Truth started")
  cha := make(chan int32)
  chb := make(chan float32)

  go func() {
    for {
      select {
      case a := <-cha:
        glog.Info("cha message")
        glog.Info(cha, a)
      case b := <-chb:
        glog.Info("chb message")
        glog.Info(chb, b)
      }
    }
  }()

  for _, i := range []int32{1,2,4,8,16,100} {
//    cha <- i
    chb <- float32(i)*0.35
  }

  parts := []string{"ipns", "better", "ok", "ipfs", "cargo", "better", "won"}
  switch parts[1] {
    case "ipfs":
      glog.Info("1", "ipfs")
    case "cargo", "better":
      glog.Info("2", parts[1])
    default:
      glog.Info("mismatched")
  }

  glog.Info("P224", elli.P224())
  glog.Info("P256", elli.P256())
  glog.Info("P384", elli.P384())
  glog.Info("P521", elli.P521())

  curve := elli.P521()
  //rd := strings.NewReader("NASA IS GOING TO MARS")
  rd, err := os.Open("src/truth/app/test.go")
  if err != nil {
    glog.Error("failed to open file", err)
    return
  }

  prikey, err := ecdsa.GenerateKey(curve, rd)
  if err != nil {
    glog.Error("failed to generate prikey", err)
    return
  }

  pubkey := prikey.Public()
  glog.Info("pri ", prikey)
  glog.Info("pri.D ", prikey.D)
  glog.Info("pub", pubkey)
//  glog.Info("pub.X", pubkey.X)
//  glog.Info("pub.Y", pubkey.Y)
}
