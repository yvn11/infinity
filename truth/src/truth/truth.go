package truth

import (
  "fmt"
  "log"
  pb "truth/iface/service"
  _ "github.com/grpc/grpc"
)

const (
  port = ":17351"
)

func main() {
  fd, err := net.Listen("tcp", port)
  if err != nil {
    log.Fatalf("failed to listen: %v", err)
  }

  svr := grpc.NewServer()
  pb.Register
}
