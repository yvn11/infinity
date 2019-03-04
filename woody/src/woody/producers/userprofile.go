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
  "strconv"
  "encoding/csv"
  "encoding/json"
)

var (
  checkin_csv = "/data/foursquare/dataset_tist2015/dataset_TIST2015_Checkins.txt"
  city_csv = "/data/foursquare/dataset_tist2015/dataset_TIST2015_Cities.txt"
  poi_csv = "/data/foursquare/dataset_tist2015/dataset_TIST2015_POIs.txt"
)

type CheckinStreamProducer struct {
  pro sarama.AsyncProducer
  checkin_ev chan []string
  city_ev chan []string
  poi_ev chan []string
}

type CheckinEvent struct {
  UserID string `json:"user_id,omitempty"`
  VenueID string `json:"venue_id,omitempty"`
  UtcTime string `json:"utc_time,omitempty"`
  TzOffset string `json:"tz_offset,omitempty"`
  CreatedAt string `json:"created_at,omitempty"`
  UpdatedAt string `json:"updated_at,omitempty"`
}

type CityEvent struct {
  Name string `json:"name,omitempty"`
  Lat float64 `json:"lat,omitempty"`
  Lon float64 `json:"lon,omitempty"`
  CountryCode string `json:"country_code,omitempty"`
  CountryName string `json:"country_name,omitempty"`
  Type string `json:"type,omitempty"`
  CreatedAt string `json:"created_at,omitempty"`
  UpdatedAt string `json:"updated_at,omitempty"`
}

type PoiEvent struct {
  VenueID string `json:"venue_id,omitempty"`
  Lat float64 `json:"lat,omitempty"`
  Lon float64 `json:"lon,omitempty"`
  VenueCate string `json:"venue_cate,omitempty"`
  CountryCode string `json:"country_code,omitempty"`
  CreatedAt string `json:"created_at,omitempty"`
  UpdatedAt string `json:"updated_at,omitempty"`
}

func NewCheckinStreamProducer() *CheckinStreamProducer {
  var ret CheckinStreamProducer
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

  ret.checkin_ev = make(chan []string, 1)
  ret.city_ev = make(chan []string, 1)
  ret.poi_ev = make(chan []string, 1)
  return &ret
}

/** create ProducerMessage from TSV value */
func (p *CheckinStreamProducer) checkin_msg(val []string) (*sarama.ProducerMessage, error) {
  now := strconv.FormatInt(time.Now().Unix(), 10)

  jdata, err := json.Marshal(&CheckinEvent{
    UserID: val[0],
    VenueID: val[1],
    UtcTime: val[2],
    TzOffset: val[3],
    CreatedAt: now,
    UpdatedAt: now,
  })
  if err != nil {
    glog.Error("failed to marshal click event: ", err)
    return nil, err
  }

  return &sarama.ProducerMessage{
    Topic: woody.TOPIC_CHECKIN,
    Key: sarama.StringEncoder(val[0]),
    Value: sarama.ByteEncoder(jdata),
    Timestamp: time.Now(),
  //Partition: 1,
  }, nil
}

func (p *CheckinStreamProducer) city_msg(val []string) (*sarama.ProducerMessage, error) {
  lat, _ := strconv.ParseFloat(val[1], 64)
  lon, _ := strconv.ParseFloat(val[2], 64)
  now := strconv.FormatInt(time.Now().Unix(), 10)

  jdata, err := json.Marshal(&CityEvent{
    Name: val[0],
    Lat: lat,
    Lon: lon,
    CountryCode: val[3],
    CountryName: val[4],
    Type: val[5],
    CreatedAt: now,
    UpdatedAt: now,
  })
  if err != nil {
    glog.Error("failed to marshal buy event: ", err)
    return nil, err
  }

  return &sarama.ProducerMessage{
    Topic: woody.TOPIC_CITY,
    Key: sarama.StringEncoder(val[0]),
    Value: sarama.ByteEncoder(jdata),
    Timestamp: time.Now(),
  }, nil
}

func (p *CheckinStreamProducer) poi_msg(val []string) (*sarama.ProducerMessage, error) {
  lat, _ := strconv.ParseFloat(val[1], 64)
  lon, _ := strconv.ParseFloat(val[2], 64)
  now := strconv.FormatInt(time.Now().Unix(), 10)

  jdata, err := json.Marshal(&PoiEvent{
    VenueID: val[0],
    Lat: lat,
    Lon: lon,
    VenueCate: val[3],
    CountryCode: val[4],
    CreatedAt: now,
    UpdatedAt: now,
  })
  if err != nil {
    glog.Error("failed to marshal buy event: ", err)
    return nil, err
  }

  return &sarama.ProducerMessage{
    Topic: woody.TOPIC_POI,
    Key: sarama.StringEncoder(val[0]),
    Value: sarama.ByteEncoder(jdata),
    Timestamp: time.Now(),
  }, nil
}

func (p *CheckinStreamProducer) fakeKeepRead(path string, ev chan []string) {
  for {
    glog.Infof("round begin[%s]: %v\n", path, time.Now())
    p.FromTSV(path, ev)
  }
}

func (p *CheckinStreamProducer) Run() {
  sig := make(chan os.Signal, 1)
  signal.Notify(sig, os.Interrupt)

  go p.fakeKeepRead(city_csv, p.city_ev)
  go p.fakeKeepRead(poi_csv, p.poi_ev)
  go p.fakeKeepRead(checkin_csv, p.checkin_ev)
  var sent_nr int

  ProducerLoop:
  for {
    var msg *sarama.ProducerMessage
    var err error

    select {
    case val := <-p.checkin_ev:
      msg, err = p.checkin_msg(val)
    case val := <-p.city_ev:
      msg, err = p.city_msg(val)
    case val := <-p.poi_ev:
      msg, err = p.poi_msg(val)
    }

    if err != nil {
      glog.Error("failed to create msg", err)
      continue
    }

    select {
    case p.pro.Input() <-msg:
      sent_nr++
      //if sent_nr > 1000 { break ProducerLoop }
      glog.Infof("sent[%d]: %v\n", sent_nr, time.Now())
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

func (p *CheckinStreamProducer) FromTSV(path string, ev chan []string) error {
  fd, err := os.Open(path)
  if err != nil {
    glog.Error("failed to open ", path, ": ", err)
    return err
  }
  defer fd.Close()

  rd := csv.NewReader(fd)
  rd.Comma = '\t';
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
