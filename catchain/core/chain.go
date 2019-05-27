package core

import (
  "github.com/zex/catchain/store"
  "math/big"
  "fmt"
  "sync"
)

var (
  TypeBlock = []byte("block/")
  TypeStat = []byte("stat/")
  BigOne = big.NewInt(1)
)

type Chain struct {
  blocks *store.Store
  mux *sync.Mutex
}

func NewChain() *Chain {
  return &Chain{
    blocks: store.NewStore(),
    mux: &sync.Mutex{},
  }
}

func (chain *Chain) PutLength(l *big.Int) {
  chain.mux.Lock()
  chain.blocks.Put(append(TypeStat, []byte("length")...), []byte(l.String()))
  chain.mux.Unlock()
}

func (chain *Chain) Length() *big.Int {
  data := chain.blocks.Get(append(TypeStat, []byte("length")...))
  ret := big.NewInt(0)

  if data == nil {
    return ret
  }
  ret.SetString(string(data), 10)
  return ret
}
/**
func (chain *Chain) IncLength() {
  l := chain.Length()
  l = l.Add(l, BigOne)
  chain.PutLength(l)
}

func (chain *Chain) DecLength() {
  l := chain.Length()
  l = l.Sub(l, BigOne)
  chain.PutLength(l)
}
*/
func (chain *Chain) AddRaw(data []byte) error {
  last, err := chain.LastBlock()
  if err != nil {
    return err
  }

  var prev []byte

  if last != nil {
    prev = last.Hash()
  }

  l := chain.Length()
  l = l.Add(l, BigOne)
  blk := NewBlock(l, prev, data)
  if err = chain.PutBlock(blk); err == nil {
    chain.PutLength(l)
  }
  return err
}

func (chain Chain) LastBlock() (*Block, error) {
// return chain.blocks[len(chain.blocks)-1];
  l := chain.Length()
  hash, err := chain.GetHashByNum(l.Sub(l, BigOne))
  if err != nil {
    return nil, err
  }
  return chain.GetBlock(hash)
}

func (chain Chain) GetHashByNum(n *big.Int) ([]byte, error) {
  //impl
  return nil, nil
}

func (chain Chain) GetBlock(key []byte) (*Block, error) {
  data := chain.blocks.Get(append(TypeBlock, key...))
  if data == nil {
    return nil, nil
  }

  ret := &Block{}
  if err := ret.Decode(data); err != nil {
    return nil, err
  }
  return ret, nil
}

func (chain Chain) HasBlock(Key []byte) (bool, error) {
  return chain.blocks.Has(append(TypeBlock, Key...))
}

func (chain *Chain) PutBlock(b *Block) error {
  if found, _ := chain.HasBlock(b.Hash()); found {
    return fmt.Errorf("[chain] block exists")
  }

  data, err := b.Encode()
  if err != nil {
    return err
  }

  chain.mux.Lock()
  err = chain.blocks.Put(append(TypeBlock, b.Hash()...), data)
  chain.mux.Unlock()
  return err
}

func (chain *Chain) Close() {
  chain.blocks.Close()
}

func (chain Chain) ListBlockKeys() ([][]byte, error) {
  return chain.blocks.ListKeys(TypeBlock)
}
/**
func (chain *Chain) Delete(key []byte) error {
  err := chain.blocks.Delete(key)
  if err == nil {
    chain.DecLength()
  }
  return err
}

func (chain *Chain) Clear() error {
  keys, err := chain.ListBlockKeys()
  if err != nil {
    return err
  }

  for _, k := range keys {
    if err := chain.Delete(k); err != nil {
      return err
    }
  }
  return nil
}
*/
