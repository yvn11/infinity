package main

import (
  "google.golang.org/grpc"
  "github.com/golang/glog"
  pb "proto/iface_algo"
)

var (
  server_addr = ":32190"
)

type Cli struct {
  cli *pb.FacialClient
}

func (c *Cli) reqFacialDetect() {
  rsp, err := c.cli.FacialDetect(context.Background, &pb.FacialDetectParams{
      url: "http://somewhere/pic.png",})
  if err != nil {
    glog.Error("FacialDetect error: ", err)
    return
  }
  glog.Info(rsp)
}

func (c *Cli) reqSimilarity() {
  rsp, err := c.cli.Similarity(context.Background, &pb.SimilarityParams{
      feat1: "this feature",
      feat2: "that feature",})
  if err != nil {
    glog.Error("Similarity error: ", err)
    return
  }
  glog.Info(rsp)
}

func (c *Cli) reqExtractFeature() {
  rsp, err := c.cli.ExtractFeature(context.Background, &pb.ExtractFeatureParams{
      url: "http://somewhere/pic.png",})
  if err != nil {
    glog.Error("ExtractFeature error: ", err)
    return
  }
  glog.Info(rsp)
}
func main() {
  conn, err := grpc.Dial(server_addr)
  if err != nil {
    glog.Errorf("dial failed: %v", err)
    return
  }
  defer conn.Close()

  c := &Cli{ cli := pb.NewFacialClient(conn),}
  c.reqFacialDetect(cli)
  c.reqSimilarity(cli)
  c.reqExtractFeature(cli)
}
