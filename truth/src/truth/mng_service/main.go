package main

import (
  "net"
  "log"

  sv "truth/mng"
  pb "truth_pb"
  grpc "google.golang.org/grpc"
  reflection "google.golang.org/grpc/reflection"
)

const (
  port = ":15357"
)

func main() {
  fd, err := net.Listen("tcp", port)
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
