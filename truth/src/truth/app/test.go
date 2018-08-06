package main

import (
  "os"
  "io/ioutil"
  "flag"
  "github.com/golang/glog"
  elli "crypto/elliptic"
  "crypto/ecdsa"
  "crypto/rsa"
  "crypto/rand"
  "crypto/sha256"
  "encoding/pem"
  "crypto/x509"
)

func do_ecdsa() {
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

func do_rsa() {
  rd := rand.Reader
  //rd := strings.NewReader("NASA IS GOING TO MARS")
  prikey, err := rsa.GenerateKey(rd, 1024)
  if err != nil {
    glog.Error("failed to generate prikey", err)
    return
  }

  pubkey := prikey.Public()
  glog.Info("pri ", prikey)
  glog.Info("pri.D ", prikey.D)
  glog.Info("pub", pubkey)
  glog.Info("N", prikey.PublicKey.N)
  glog.Info("E", prikey.PublicKey.E)

  msg := []byte("NASA IS GOING TO MARS")
  en_msg, err := rsa.EncryptOAEP(sha256.New(), rd, &prikey.PublicKey, msg, nil)
  if err != nil {
    glog.Error("failed to encrypt msg: ", err)
    return
  }

  glog.Info(en_msg, len(en_msg))

  de_msg, err := rsa.DecryptOAEP(sha256.New(), rd, prikey, en_msg, nil)
  if err != nil {
    glog.Error("failed to decrypt msg: ", err)
    return
  }

  glog.Info("expect: ", msg)
  glog.Info("answer: ", de_msg)
  glog.Info(string(de_msg), len(de_msg))

  dump_key(prikey)
}

func dump_key(prikey *rsa.PrivateKey) {
  pem_pri := pem.EncodeToMemory(&pem.Block{
    Type: "Truth RSA Private",
    Bytes: x509.MarshalPKCS1PrivateKey(prikey),
  })
  ioutil.WriteFile("pri.key", pem_pri, 0644)

  pem_pub := pem.EncodeToMemory(&pem.Block{
    Type: "Truth RSA Public",
    Bytes: x509.MarshalPKCS1PublicKey(&prikey.PublicKey),
  })
  ioutil.WriteFile("pub.key", pem_pub, 0644)
}

func load_key() {
}

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

  do_ecdsa()
  do_rsa()
}
