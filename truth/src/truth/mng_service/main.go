package main

import (
  "net"
  "github.com/golang/glog"
  "fmt"

  cfg "truth/config"
  sv "truth/mng"
  pb "truth_pb"
  grpc "google.golang.org/grpc"
  reflection "google.golang.org/grpc/reflection"
)

func main() {
  glog.Infof("Truth management server %s @ %s", cfg.VERSION, cfg.RPC_MNG_PORT)
  port := fmt.Sprintf(":%s", cfg.RPC_MNG_PORT)
  fd, err := net.Listen("tcp", port)
  if err != nil {
    glog.Fatalf("failed to listen: %v", err)
  }

  grpc_srv := grpc.NewServer()
  pb.RegisterTruthManagementServer(grpc_srv, &sv.TruthManagementServer{})
	reflection.Register(grpc_srv)

  if err := grpc_srv.Serve(fd); err != nil {
    glog.Fatalf("failed to start server: %v", err)
  }
}
