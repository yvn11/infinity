package truth

import (
  "github.com/golang/glog"
  "sync"

  "github.com/syndtr/goleveldb/leveldb"
)


type TruthDB struct {
  mux: sync.Mutex
  db: leveldb.DB
}

func (db *TruthDB) Get(key []byte) (val []byte, error) {
  val, err := db.db.Get(key, nil)
  if err != nil {
    glog.Fatalf("get failed: %v", err)
    return nil, err
  }
  return val, nil
}

func (db *TruthDB) Set(key, value []byte) error {
  err := db.db.Put(key, value, nil)
  if err != nil {
    glog.Fatalf("set failed: %v", err)
    return err
  }
  return nil
}
