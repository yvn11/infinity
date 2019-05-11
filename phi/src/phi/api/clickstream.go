package api

import (
  "encoding/json"
  "net/http"
  "fmt"
  // "sort"
  // "strings"
  "github.com/golang/glog"
  cql "github.com/gocql/gocql"
  "phi/common"
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
  cass_sess *cql.Session
}

func NewClickstreamApi() *ClickstreamApi {
  return &ClickstreamApi{
    cass_sess: CassSession("phi_clickstream"),
  }
}

func (p *ClickstreamApi) map_scan(q string) (metrics []map[string]interface{}) {
  //var metrics []map[string]interface{}

  iter := p.cass_sess.Query(q).Iter()
  for {
    row := make(map[string]interface{})
    if ok := iter.MapScan(row); !ok {
      iter.Close()
      break
    }
    metrics = append(metrics, row)
  }
  glog.Info("result: ", len(metrics))
  return
}

/**
 * gt: count greater than value specified
 * limit: rows per request
 */
func (p *ClickstreamApi) MetricsItemClick(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", phi.CurrentScope(), r.URL)

  gt := r.URL.Query().Get("gt")
  if len(gt) == 0 { gt = "10" }
  limit := r.URL.Query().Get("limit")
  if len(limit) == 0 { limit = "100" }

  q := fmt.Sprintf(
    `SELECT * FROM item_click WHERE click_count > %s LIMIT %s ALLOW FILTERING`,
    gt, limit)

  metrics := p.map_scan(q)

  // sort by updated_at
  //sort.Sort(ByUpdatedAt(metrics))
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

func (p *ClickstreamApi) MetricsSessionClick(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", phi.CurrentScope(), r.URL)

  gt := r.URL.Query().Get("gt")
  if len(gt) == 0 { gt = "10" }
  limit := r.URL.Query().Get("limit")
  if len(limit) == 0 { limit = "100" }

  q := fmt.Sprintf(
    `SELECT * FROM session_click WHERE click_count > %s LIMIT %s ALLOW FILTERING`,
    gt, limit)

  metrics := p.map_scan(q)

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

func (p *ClickstreamApi) MetricsItemQuan(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", phi.CurrentScope(), r.URL)
  glog.Infof("%s %v", phi.CurrentScope(), r.URL.Query())

  gt := r.URL.Query().Get("gt")
  if len(gt) == 0 { gt = "10" }
  limit := r.URL.Query().Get("limit")
  if len(limit) == 0 { limit = "100" }

  q := fmt.Sprintf(
    `SELECT * FROM item_quan WHERE quan_bought > %s LIMIT %s ALLOW FILTERING`,
    gt, limit)

  metrics := p.map_scan(q)

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

func (p *ClickstreamApi) MetricsSessionQuan(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", phi.CurrentScope(), r.URL)

  gt := r.URL.Query().Get("gt")
  if len(gt) == 0 { gt = "10" }
  limit := r.URL.Query().Get("limit")
  if len(limit) == 0 { limit = "100" }

  q := fmt.Sprintf(
    `SELECT * FROM session_quan WHERE quan_bought > %s LIMIT %s ALLOW FILTERING`,
    gt, limit)

  metrics := p.map_scan(q)

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

func (p *ClickstreamApi) MetricsCategoryClick(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", phi.CurrentScope(), r.URL)

  gt := r.URL.Query().Get("gt")
  if len(gt) == 0 { gt = "10" }
  limit := r.URL.Query().Get("limit")
  if len(limit) == 0 { limit = "100" }

  q := fmt.Sprintf(
    `SELECT * FROM category_click WHERE click_count > %s LIMIT %s ALLOW FILTERING`,
    gt, limit)

  metrics := p.map_scan(q)

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

/**
 * ev: event type, default `click`
 * limit: rows per request
 */
func (p *ClickstreamApi) MetricsEventStream(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", phi.CurrentScope(), r.URL)

  ev := r.URL.Query().Get("ev")
  if len(ev) == 0 { ev = "click" }
  limit := r.URL.Query().Get("limit")
  if len(limit) == 0 { limit = "100" }

  q := fmt.Sprintf(
    `SELECT * FROM total_event WHERE event='%s' LIMIT %s ALLOW FILTERING`,
    ev, limit)

  metrics := p.map_scan(q)

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

func (p *ClickstreamApi) SetHandler(mux *http.ServeMux) {
  mux.HandleFunc("/v1/metrics/click/item_click", p.MetricsItemClick)
  mux.HandleFunc("/v1/metrics/click/session_click", p.MetricsSessionClick)
  mux.HandleFunc("/v1/metrics/click/category_click", p.MetricsCategoryClick)
  mux.HandleFunc("/v1/metrics/click/event_stream", p.MetricsEventStream)
  mux.HandleFunc("/v1/metrics/click/item_quan", p.MetricsItemQuan)
  mux.HandleFunc("/v1/metrics/click/session_quan", p.MetricsSessionQuan)
  //mux.HandleFunc("/v1/metrics/purchase_delta", p.MetricsPurchaseDelta)
}
