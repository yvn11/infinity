package main

import (
  "net"
  "log"

  "os"
  "os/signal"
  "syscall"

  cfg "truth/config"
  sv "truth/public"
  pb "truth_pb"
  grpc "google.golang.org/grpc"
  reflection "google.golang.org/grpc/reflection"
)

func main() {
  log.Printf("Truth public server %s @ %s", cfg.VERSION, cfg.RPC_PUBLIC_PORT)

  fd, err := net.Listen("tcp", cfg.RPC_PUBLIC_PORT)
  if err != nil {
    log.Fatalf("failed to listen: %v", err)
  }

  grpc_srv := grpc.NewServer()
  pb.RegisterTruthServiceServer(grpc_srv, &sv.TruthServer{})
	reflection.Register(grpc_srv)

  if err := grpc_srv.Serve(fd); err != nil {
    log.Fatalf("failed to start server: %v", err)
  }
  defer grpc_srv.GracefulStop()

  sig_chan := make(chan os.Signal, 1)
  signal.Notify(sig_chan, syscall.SIGINT, syscall.SIGTERM)
  log.Printf("Public service stopped")
}
