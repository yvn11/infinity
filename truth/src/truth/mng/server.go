// management service over rpc
package management

import (
  "log"

  cfg "truth/config"
	context "golang.org/x/net/context"
  pb "truth_pb"
)

type TruthManagementServer struct {}

// Server version
func (s *TruthManagementServer) Version(ctx context.Context, in *pb.Request) (*pb.VersionResponse, error) {
  log.Printf("Version (%v, %v)", ctx, in)
  return &pb.VersionResponse{&pb.OpStatus{pb.StatusCode_Ok, ""}, cfg.VERSION}, nil
}

// Stop public service
func (c *TruthManagementServer) Stop(ctx context.Context, in *pb.Request) (*pb.OpStatus, error) {
  log.Printf("Stop (%v, %v)", ctx, in)
  return &pb.OpStatus{pb.StatusCode_Ok, ""}, nil
}
