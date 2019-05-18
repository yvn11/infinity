package catchain

import (
  "crypto/sha256"
  "time"
)

type Block struct {
  ts_sec int64
  prev_hash [32]byte
  hash [32]byte
}

func NewBlock(prev [32]byte, data []byte) *Block {
  return &Block{
    ts_sec: time.Now().Unix(),
    prev_hash: prev,
    hash: sha256.Sum256(data),
  }
}

func (block *Block) Hash() [32]byte {
  return block.hash
}
