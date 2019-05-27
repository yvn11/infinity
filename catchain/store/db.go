package store

import (
  "github.com/syndtr/goleveldb/leveldb"
  "github.com/syndtr/goleveldb/leveldb/util"
  "github.com/zex/catchain/common"
  "log"
  "fmt"
)

type Store struct {
  db *leveldb.DB
}

func NewStore() *Store {
  db, err := leveldb.OpenFile(common.StorePath, nil)
  if err != nil {
    log.Panic(err)
    return nil
  }
  return &Store{db: db,}
}

func (s *Store) Close() {
  s.db.Close()
}

func (s *Store) Get(key []byte) []byte {
  if key == nil {
    return nil
  }

  val, err := s.db.Get(key, nil)
  if err != nil {
    return nil
  }
  return val
}

func (s *Store) Put(key, val []byte) error {
  if key == nil {
    return fmt.Errorf("[store] invalid key")
  }
  return s.db.Put(key, val, nil)
}

func (s *Store) Has(key []byte) (bool, error) {
  return s.db.Has(key, nil)
}

func (s *Store) Delete(key []byte) error {
  if key == nil {
    return nil
  }
  return s.db.Delete(key, nil)
}

func (s *Store) ListKeys(prev []byte) ([][]byte, error){
  var ret [][]byte

  it := s.db.NewIterator(util.BytesPrefix(prev), nil)
  for it.Next() {
    key := make([]byte, len(it.Key()))
    copy(key, it.Key())
    ret = append(ret, key)
  }

  it.Release()
  if it.Error() != nil {
    return nil, it.Error()
  }

  return ret, nil
}
