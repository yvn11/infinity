package producers

import (
  "github.com/Shopify/sarama"
  "github.com/golang/glog"
  "io"
  "os"
  "os/signal"
  "woody/common"
  "time"
  "strings"
  "encoding/csv"
  "encoding/json"
)

var (
  click_tsv = "/data/yoochoose/yoochoose-clicks.dat"
  buy_tsv = "/data/yoochoose/yoochoose-buys.dat"
)

type ClickstreamProducer struct {
  pro sarama.AsyncProducer
  click_ev chan []string
  buy_ev chan []string
}

type ClickEvent struct {
  SessionID string `json:"session_id,omitempty"`
  Timestamp string `json:"timestamp,omitempty"`
  ItemID string `json:"item_id,omitempty"`
  Category string `json:"category,omitempty"`
}

type BuyEvent struct {
  SessionID string `json:"session_id,omitempty"`
  Timestamp string `json:"timestamp,omitempty"`
  ItemID string `json:"item_id,omitempty"`
  Price string `json:"price,omitempty"`
  Quantity string `json:"quantity,omitempty"`
}

func NewClickstreamProducer() *ClickstreamProducer {
  var ret ClickstreamProducer
  var err error

  cfg := sarama.NewConfig()
  cfg.Version = woody.KAFKA_VERSION
  cfg.Producer.Return.Successes = true
  cfg.Producer.Partitioner = sarama.NewRandomPartitioner

  brks := strings.Split(*woody.Brokers, ",")
  glog.Info("version: ", cfg.Version, " brokers: ", brks)

  if ret.pro, err = sarama.NewAsyncProducer(brks, cfg); err != nil {
    // panic here
    glog.Fatal("create producer failed: ", err)
  }

  ret.click_ev = make(chan []string, 1)
  ret.buy_ev = make(chan []string, 1)
  return &ret
}

/** create ProducerMessage from TSV value */
func (p *ClickstreamProducer) click_msg(val []string) (*sarama.ProducerMessage, error) {
  click_json, err := json.Marshal(&ClickEvent{
    SessionID: val[0],
    Timestamp: val[1],
    ItemID: val[2],
    Category: val[3],
  })
  if err != nil {
    glog.Error("failed to marshal click event: ", err)
    return nil, err
  }

  return &sarama.ProducerMessage{
    Topic: woody.TOPIC_CLICK,
    Key: sarama.StringEncoder(val[0]),
    Value: sarama.ByteEncoder(click_json),
    Timestamp: time.Now(),
  //Partition: 1,
  }, nil
}

func (p *ClickstreamProducer) buy_msg(val []string) (*sarama.ProducerMessage, error) {
  buy_json, err := json.Marshal(&BuyEvent{
    SessionID: val[0],
    Timestamp: val[1],
    ItemID: val[2],
    Price: val[3],
    Quantity: val[4],
  })
  if err != nil {
    glog.Error("failed to marshal buy event: ", err)
    return nil, err
  }

  return &sarama.ProducerMessage{
    Topic: woody.TOPIC_BUY,
    Key: sarama.StringEncoder(val[0]),
    Value: sarama.ByteEncoder(buy_json),
    Timestamp: time.Now(),
  }, nil
}

func (p *ClickstreamProducer) Run() {
  sig := make(chan os.Signal, 1)
  signal.Notify(sig, os.Interrupt)

  go p.FromTSV(click_tsv, p.click_ev)
  go p.FromTSV(buy_tsv, p.buy_ev)
  // var sent_nr int

  ProducerLoop:
  for {
    var msg *sarama.ProducerMessage
    var err error

    select {
    case val := <-p.click_ev:
      msg, err = p.click_msg(val)
    case val := <-p.buy_ev:
      msg, err = p.buy_msg(val)
    }

    if err != nil {
      glog.Error("failed to create msg", err)
      continue
    }

    select {
    case p.pro.Input() <-msg:
      //sent_nr++
      //if sent_nr > 1000 { break ProducerLoop }
      glog.Infof("sent[]: %v\n", msg)
    case <-sig:
      p.pro.AsyncClose()
      glog.Info("click-stream producer quit")
      break ProducerLoop
    case r := <-p.pro.Successes():
      glog.Info("ok: ", r)
    case r := <-p.pro.Errors():
      glog.Info("err: ", r)
    }
  }
}

func (p *ClickstreamProducer) FromTSV(path string, ev chan []string) error {
  fd, err := os.Open(path)
  if err != nil {
    glog.Error("failed to open ", path, ": ", err)
    return err
  }
  defer fd.Close()

  rd := csv.NewReader(fd)
  for {
    rec, err := rd.Read()
    if err == io.EOF { break }
    if err != nil {
      glog.Errorf("read failed: %v", err)
      break
    }

    ev<-rec
  }

  return nil
}
