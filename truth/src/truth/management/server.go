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
func (c *TruthManagementServer) Stop(ctx context.Context, in *pb.DummyRequest) (*pb.OpStatus, error) {
  log.Printf("Stop (%v, %v)", ctx, in)
  return &pb.OpStatus{pb.StatusCode_Ok, ""}, nil
}

// List available services
func (s *TruthManagementServer) ListServices(ctx context.Context, in *pb.Request) (*pb.ServiceResponse, error) {
  log.Printf("ListServices (%v, %v)", ctx, in)
  return &pb.ServiceResponse{&pb.OpStatus{pb.StatusCode_Ok, ""}, nil}, nil
}

// Find peer by peer identifier
func (s *TruthManagementServer) FindPeerWithID(ctx context.Context, in *pb.FindPeerRequest) (*pb.Peer, error) {
  log.Printf("FindPeerWithID (%v, %v)", ctx, in)
  return &pb.Peer{}, nil
}

// Find peer by peer name
func (s *TruthManagementServer) FindPeerWithName(ctx context.Context, in *pb.FindPeerRequest) (*pb.Peer, error) {
  log.Printf("FindPeerWithName (%v, %v)", ctx, in)
  return &pb.Peer{}, nil
}

// Send a message
func (s *TruthManagementServer) SendMessage(ctx context.Context, in *pb.Message) (*pb.OpStatus, error) {
  log.Printf("SendMessage (%v, %v)", ctx, in)
  return &pb.OpStatus{pb.StatusCode_Ok, ""}, nil
}

// List unread messages of peer
func (s *TruthManagementServer) ListUnreadMessage(ctx context.Context, in *pb.Request) (*pb.MessageResponse, error){
  log.Printf("ListUnreadMessage (%v, %v)", ctx, in)
  return &pb.MessageResponse{&pb.OpStatus{pb.StatusCode_Ok, ""}, nil}, nil
}
