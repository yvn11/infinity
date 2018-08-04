package main

import (
  "github.com/golang/glog"
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


var (
  sender = pb.Peer{
      Id: "truth_keeper_0001",
      Name: "Truth Keeper",
    }
  )

func dial_remote(host string, port int32) {
  var opts []grpc.DialOption
  opts = append(opts, grpc.WithInsecure())
  remote_addr := fmt.Sprintf("%s:%d", host, port)

  conn, err := grpc.Dial(remote_addr, opts...)
  if err != nil {
    glog.Fatalf("failed to dial [%s]: %v", remote_addr, err)
  }
  defer conn.Close()

  cli := pb.NewTruthManagementClient(conn)

  ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
  defer cancel()

  ver, err := cli.Version(ctx, &pb.Request{
    Sender: &sender})

  if err != nil {
    glog.Errorf("failed to invoke Version: %v", err)
  } else {
    glog.Infof("remote version: [%v]", ver)
  }

  rsp, err := cli.SysInfo(ctx, &pb.Request{
    Sender: &sender})

  if err != nil {
    glog.Errorf("failed to invoke SysInfo: %v", err)
  } else {
    glog.Infof("ru: [%v]", rsp)
  }
}

func main() {
  dial_remote(truth_host, truth_port)
}

