package api

import (
  "flag"
  "encoding/json"
  "net/http"
  "sort"
  "strings"
  "github.com/rs/cors"
  "github.com/golang/glog"
  cql "github.com/gocql/gocql"
  "woody/common"
)

/**
type MetricsItemClick struct {
  ItemID string `json:"item_id,omitempty"`
  ClickCount string `json:"click_count,omitempty"`
  CreatedAt string `json:"created_at,omitempty"`
  UpdatedAt string `json:"updated_at,omitempty"`
}

type MetricsSessionClick struct {
  SessionID string `json:"session_id,omitempty"`
  ClickCount string `json:"click_count,omitempty"`
  CreatedAt string `json:"created_at,omitempty"`
  UpdatedAt string `json:"updated_at,omitempty"`
}

type MetricsSessionQuan struct {
  SessionID string `json:"session_id,omitempty"`
  QuanBought string `json:"quan_bought,omitempty"`
  CreatedAt string `json:"created_at,omitempty"`
  UpdatedAt string `json:"updated_at,omitempty"`
}

type MetricsItemQuan struct {
  ItemID string `json:"item_id,omitempty"`
  QuanBought string `json:"quan_bought,omitempty"`
  CreatedAt string `json:"created_at,omitempty"`
  UpdatedAt string `json:"updated_at,omitempty"`
}

type ByUpdatedAt []ResopnseMap

func (by ByUpdatedAt) Less(i, j int) bool {
  return by[i].UpdatedAt.Unix() < by[j].UpdatedAt.Unix()
}
func (by ByUpdatedAt) Swap(i, j int) { by[i], by[j] = by[j], by[i] }
func (by ByUpdatedAt) Len() int { return len(by) }
*/

type ClickstreamApi struct {
  cass_conf *cql.ClusterConfig
  cass_sess *cql.Session
}

func NewClickstreamApi() *ClickstreamApi {
  srv := strings.Split(*woody.CassCluster, ",")
  glog.Infof("cass cluster: %v:%d apiserver: %v", srv, *woody.CassPort, *woody.ApiAddr)
  if len(srv) == 0 { glog.Fatal("cassandra cluster not given") }

  var err error
  var p ClickstreamApi
  p.cass_conf = cql.NewCluster()
  p.cass_conf.Hosts = srv
  p.cass_conf.CQLVersion = *woody.CQLVersion
  p.cass_conf.Keyspace = "woody_clickstream"
  p.cass_conf.Port = *woody.CassPort
  p.cass_conf.IgnorePeerAddr = true
  p.cass_conf.Consistency = cql.One
  p.cass_conf.Authenticator = cql.PasswordAuthenticator{
    Username: *woody.CassUser,
    Password: *woody.CassPass,
  }

  if p.cass_sess, err = p.cass_conf.CreateSession(); err != nil {
    glog.Fatal("failed to create cassandra session: ", err)
  }

  return &p
}

func (p *ClickstreamApi) metrics_item_click(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", woody.CurrentScope(), r.URL)
  var metrics []map[string]interface{}

  iter := p.cass_sess.Query(`SELECT * FROM item_click`).Iter()
  for {
    row := make(map[string]interface{})
    if ok := iter.MapScan(row); !ok {
      iter.Close()
      break
    }
    glog.Info(row)
    metrics = append(metrics, row)
  }

  // sort by updated_at
  sort.Sort(ByUpdatedAt(metrics))
  data, err := json.Marshal(&struct{
		Response []map[string]interface{} `json:"response,omitempty"`
  }{ Response: metrics, })
  if err != nil {
    glog.Error("marshal failed: ", err)
    w.WriteHeader(http.StatusInternalServerError)
    return
  }

  w.WriteHeader(http.StatusOK)
  w.Write(data)
}

func (p *ClickstreamApi) metrics_session_click(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", woody.CurrentScope(), r.URL)
  var metrics []map[string]interface{}

  iter := p.cass_sess.Query(`SELECT * FROM session_click`).Iter()
  for {
    row := make(map[string]interface{})
    if ok := iter.MapScan(row); !ok {
      iter.Close()
      break
    }
    glog.Info(row)
    metrics = append(metrics, row)
  }

  // sort by updated_at
  data, err := json.Marshal(&struct{
		Response []map[string]interface{} `json:"response,omitempty"`
  }{ Response: metrics, })
  if err != nil {
    glog.Error("marshal failed: ", err)
    w.WriteHeader(http.StatusInternalServerError)
    return
  }

  w.WriteHeader(http.StatusOK)
  w.Write(data)
}

func (p *ClickstreamApi) metrics_item_quan(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", woody.CurrentScope(), r.URL)
  var metrics []map[string]interface{}

  iter := p.cass_sess.Query(`SELECT * FROM item_quan`).Iter()
  for {
    row := make(map[string]interface{})
    if ok := iter.MapScan(row); !ok {
      iter.Close()
      break
    }
    glog.Info(row)
    metrics = append(metrics, row)
  }

  // sort by updated_at
  data, err := json.Marshal(&struct{
		Response []map[string]interface{} `json:"response,omitempty"`
  }{ Response: metrics, })
  if err != nil {
    glog.Error("marshal failed: ", err)
    w.WriteHeader(http.StatusInternalServerError)
    return
  }

  w.WriteHeader(http.StatusOK)
  w.Write(data)
}

func (p *ClickstreamApi) metrics_session_quan(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", woody.CurrentScope(), r.URL)
  var metrics []map[string]interface{}

  iter := p.cass_sess.Query(`SELECT * FROM session_quan`).Iter()
  for {
	  row := make(map[string]interface{})
    if ok := iter.MapScan(row); !ok {
      iter.Close()
      break
    }
    metrics = append(metrics, row)
  }

  // sort by updated_at
  data, err := json.Marshal(&struct{
		Response []map[string]interface{} `json:"response,omitempty"`
  }{ Response: metrics, })
  if err != nil {
    glog.Error("marshal failed: ", err)
    w.WriteHeader(http.StatusInternalServerError)
    return
  }

  w.WriteHeader(http.StatusOK)
  w.Write(data)
}

func (p *ClickstreamApi) Start() {
  flag.Parse()
  mux := http.NewServeMux()
  mux.HandleFunc("/v1/metrics/item_click", p.metrics_item_click)
  mux.HandleFunc("/v1/metrics/session_click", p.metrics_session_click)
  mux.HandleFunc("/v1/metrics/item_quan", p.metrics_item_quan)
  mux.HandleFunc("/v1/metrics/session_quan", p.metrics_session_quan)
  //mux.HandleFunc("/v1/metrics/purchase_delta", p.metrics_purchase_delta)

  origins := strings.Split(*woody.Origins, ",")
  handler := cors.New(cors.Options{
      AllowedOrigins: origins,
      AllowCredentials: true,
      Debug: true,
    }).Handler(mux)

  glog.Info("Running on ", *woody.ApiAddr)
  glog.Fatal(http.ListenAndServe(*woody.ApiAddr, handler))
}
