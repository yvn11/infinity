package truth

import (
  "fmt"
  "log"
  pb "truth/iface/service"
  _ "truth/truth_server"
  _ "github.com/grpc/grpc"
  _ "github.com/grpc/reflection"
)

const (
  port = ":17351"
)

func main() {
  fd, err := net.Listen("tcp", port)
  if err != nil {
    log.Fatalf("failed to listen: %v", err)
  }

  grpc_srv := grpc.NewServer()
  pb.RegisterTruthServiceServer(grpc_srv, &TruthServer{})
	reflection.Register(grpc_srv)
  if err := grpc_srv.Serve(fd); err != nil {
    log.Fatalf("failed to start server: %v", err)
  }
}
