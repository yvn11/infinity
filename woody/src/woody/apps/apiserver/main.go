package main

import (
  "flag"
  "strings"
  "net/http"
  "github.com/golang/glog"
  "github.com/rs/cors"
  "woody/api"
  "woody/common"
)

type App struct {
  click_api *api.ClickstreamApi
  profile_api *api.UserProfileApi
  vehicle_api *api.VehicleApi
}

func NewApp() *App {
  return &App{
    click_api: api.NewClickstreamApi(),
    profile_api: api.NewUserProfileApi(),
    vehicle_api: api.NewVehicleApi(),
    }
}

func (app *App) Start() {
  flag.Parse()

  mux := http.NewServeMux()
  app.click_api.SetHandler(mux)
  app.profile_api.SetHandler(mux)
  app.vehicle_api.SetHandler(mux)

  origins := strings.Split(*woody.Origins, ",")
  handler := cors.New(cors.Options{
      AllowedOrigins: origins,
      AllowCredentials: true,
      Debug: true,
    }).Handler(mux)

  glog.Info("Running on ", *woody.ApiAddr)
  glog.Info("Allowed origins: ", origins)
  glog.Fatal(http.ListenAndServe(*woody.ApiAddr, handler))
}

func main() {
  flag.Parse()
  NewApp().Start()
}
