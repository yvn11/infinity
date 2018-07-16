package main

import (
  "log"
  "time"
  "fmt"

	context "golang.org/x/net/context"
  grpc "google.golang.org/grpc"
  pb "truth_pb"
)

const (
  truth_host = "localhost"
  truth_port = 15357
)

func dial_remote(host string, port int32) {
  var opts []grpc.DialOption
  opts = append(opts, grpc.WithInsecure())
  remote_addr := fmt.Sprintf("%s:%d", host, port)

  conn, err := grpc.Dial(remote_addr, opts...)
  if err != nil {
    log.Fatalf("failed to dial [%s]: %v", remote_addr, err)
  }
  defer conn.Close()

  cli := pb.NewTruthManagementClient(conn)

  ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
  defer cancel()
  ver, err := cli.Version(ctx, &pb.Request{
    Sender: &pb.Peer{
      Id: "truth_keeper_0001",
      Name: "Truth Keeper",
  }})

  if err != nil {
    log.Printf("failed to invoke Version: %v", err)
  } else {
    log.Printf("remote version: [%v]", ver)
  }
}

func main() {
  dial_remote(truth_host, truth_port)
}

