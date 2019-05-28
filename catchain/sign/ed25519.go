package sign

import (
  "golang.org/x/crypto/ed25519"
  "math/rand"
)

type Algorithm struct{}

func (a Algorithm) Seed() []byte {
  ret := make([]byte, ed25519.SeedSize)
  rand.Read(ret)
  return ret
}

func (a Algorithm) PrivateKey() []byte {
  return ed25519.NewKeyFromSeed(a.Seed())
}

func (a Algorithm) PublicKey(priv []byte) []byte {
  ret, ok := ed25519.PrivateKey(priv).Public().(ed25519.PublicKey)
  if ok {
    return ret
  }
  return nil
}

func (a Algorithm) Sign(priv, msg []byte) []byte {
  return ed25519.Sign(priv, msg)
}

func (a Algorithm) Verify(pub, msg, sig []byte) bool {
  return ed25519.Verify(pub, msg, sig)
}
