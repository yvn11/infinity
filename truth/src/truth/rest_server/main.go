package main

import (
  "log"
  "fmt"
  "net/http"

  "github.com/rs/cors"
  "github.com/gorilla/mux"

  cfg "truth/config"
  hdr "truth/rest_server/handler"
)

const (
  api_root = "/api/v1"
  truth_port = "17830"
)

func start_server() {
  log.Printf("Truth rest server %s", cfg.VERSION)

  router := mux.NewRouter()
  router.Headers("Context-Type", "application/json")

  router.HandleFunc(fmt.Sprintf("%s/version", api_root), hdr.Version).Methods("GET")
  router.HandleFunc(fmt.Sprintf("%s/unread_msg", api_root), hdr.UnreadMsg).Methods("GET")
  router.HandleFunc(fmt.Sprintf("%s/list_services", api_root), hdr.ListServices).Methods("GET")
  router.HandleFunc(fmt.Sprintf("%s/find_peer", api_root), hdr.FindPeer).Methods("GET")
  router.HandleFunc(fmt.Sprintf("%s/send_msg", api_root), hdr.SendMsg).Methods("POST")

  cors_opt := cors.New(cors.Options{
    AllowedOrigins: []string{"*"},
  })
  cors_hdr := cors_opt.Handler(router)

  http.ListenAndServe(fmt.Sprintf(":%d", truth_port), cors_hdr)
}

func main() {
  start_server()
}

