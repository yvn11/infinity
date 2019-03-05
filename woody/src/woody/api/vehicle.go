package api

import (
  "net/http"
  "io/ioutil"
  "github.com/golang/glog"
  "woody/common"
)

const (
  vehicle_metrics_path = "/data/vehicle/metrics.json"
)

type VehicleApi struct {
  //cass_sess *cql.Session
}

func NewVehicleApi() *VehicleApi {
  return &VehicleApi{
    //cass_sess: CassSession("woody_userprofile"),
  }
}

func (p *VehicleApi) Metrics(w http.ResponseWriter, r *http.Request) {
  glog.Infof("%s %v", woody.CurrentScope(), r.URL)
  data, err := ioutil.ReadFile(vehicle_metrics_path)
  if err != nil {
    glog.Errorf("failed to read {}: {}", vehicle_metrics_path, err)
    w.WriteHeader(http.StatusInternalServerError)
    return
  }
  w.WriteHeader(http.StatusOK)
  w.Write(data)
}

func (p *VehicleApi) SetHandler(mux *http.ServeMux) {
  mux.HandleFunc("/v1/metrics/vehicle", p.Metrics)
}
