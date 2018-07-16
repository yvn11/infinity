package main

import (
  "net"
  "log"

  cfg "truth/config"
  sv "truth/mng"
  pb "truth_pb"
  grpc "google.golang.org/grpc"
  reflection "google.golang.org/grpc/reflection"
)

func main() {
  log.Printf("Truth management server %s @ %s", cfg.VERSION, cfg.RPC_MNG_PORT)

  fd, err := net.Listen("tcp", cfg.RPC_MNG_PORT)
  if err != nil {
    log.Fatalf("failed to listen: %v", err)
  }

  grpc_srv := grpc.NewServer()
  pb.RegisterTruthManagementServer(grpc_srv, &sv.TruthManagementServer{})
	reflection.Register(grpc_srv)

  if err := grpc_srv.Serve(fd); err != nil {
    log.Fatalf("failed to start server: %v", err)
  }
}
