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
}

func NewApp() *App {
  return &App{click_api: api.NewClickstreamApi()}
}

func (app *App) Start() {
  flag.Parse()

  mux := http.NewServeMux()
  app.click_api.SetHandler(mux)

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
