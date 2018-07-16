package main

import (
  "log"
  "fmt"
  "net/http"

  "os"
  "os/signal"
  "syscall"

  "github.com/rs/cors"
  "github.com/gorilla/mux"

  cfg "truth/config"
  hdr "truth/rest_server/handler"
)

const (
  api_root = "/api/v1"
)

func start_server() {
  log.Printf("Truth rest server %s @ %s", cfg.VERSION, cfg.REST_PUBLIC_PORT)

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

  port := fmt.Sprintf(":%s", cfg.REST_PUBLIC_PORT)
  err := http.ListenAndServe(port, cors_hdr)
  if err != nil {
    log.Fatal("Failed to start rest server: ", err)
    return
  }

  sig_chan := make(chan os.Signal, 1)
  signal.Notify(sig_chan, syscall.SIGINT, syscall.SIGTERM)
  //http.Shutdown()
  log.Printf("Rest service stopped")
}

func main() {
  start_server()
}

