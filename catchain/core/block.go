package core

import (
  "github.com/golang/protobuf/proto"
  pb "github.com/zex/catchain/common/proto"
  "crypto/sha256"
  "time"
  "math/big"
  "fmt"
)

type Block struct {
  hash []byte
  ts int64
  num *big.Int
  prev []byte
}

func NewBlock(num *big.Int, prev, data []byte) *Block {
  return &Block{
    ts: time.Now().Unix(),
    prev: prev,
    hash: Hash(data),
    num: num,
  }
}

func (b Block) String() string {
  return fmt.Sprintf("time:%d, prev:%v, self:%v, num:%s",
    b.ts, b.prev, b.hash, b.num.String())
}

func Hash(data []byte) []byte {
  h := sha256.Sum256(data)
  return h[:]
}

func (b Block) Hash() []byte {
  return b.hash
}

func (b Block) Num() *big.Int {
  return b.num
}

func (b Block) Prev() []byte {
  return b.prev
}

func (b Block) Time() int64 {
  return b.ts
}

func (b *Block) SetNum(n *big.Int) {
  b.num.Set(n)
}

func (b *Block) SetPrev(prev []byte) {
  copy(b.prev[:], prev[:])
}

func (b *Block) Encode() ([]byte, error) {
  blk := &pb.Block{
    Ts: b.ts,
    Num: []byte(b.num.String()),
    Hash: b.hash,
    Prev: b.prev,
  }

  data, err := proto.Marshal(blk)
  if err != nil {
    return nil, err
  }
  return data, nil
}

func (b *Block) Decode(data []byte) error {
  if data == nil {
    return fmt.Errorf("[block] empty data")
  }

  blk := &pb.Block{}
  if err := proto.Unmarshal(data, blk); err != nil {
    return err
  }

  b.hash = make([]byte, len(blk.Hash))
  copy(b.hash, blk.Hash)

  b.prev = make([]byte, len(blk.Prev))
  copy(b.prev, blk.Prev)

  b.num = big.NewInt(0)
  b.num.SetString(string(blk.Num), 10)
  b.ts = blk.Ts
  return nil
}

