package catchain

import (
  "time"
)

type Chain struct {
  blocks []*Block
}

func NewChain() *Chain {
  var chain Chain
  var null [32]byte
  chain.AddBlock(NewBlock(null, []byte(time.Now().String())))
  return &chain
}

func (chain *Chain) AddBlock(b *Block) {
  chain.blocks = append(chain.blocks, b)
}

func (chain *Chain) AddRaw(data []byte) {
  chain.AddBlock(NewBlock(chain.LastBlock().Hash(), data))
}

func (chain *Chain) LastBlock() *Block {
  return chain.blocks[len(chain.blocks)-1];
}
