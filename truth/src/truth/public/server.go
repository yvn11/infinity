// public service over rpc
package server

import (
  "github.com/golang/glog"

  cfg "truth/config"
	context "golang.org/x/net/context"
  pb "truth_pb"
)

type TruthServer struct {}

// List available services
func (s *TruthServer) ListServices(ctx context.Context, in *pb.Request) (*pb.ServiceResponse, error) {
  glog.Infof("ListServices (%v, %v)", ctx, in)
  return &pb.ServiceResponse{&pb.OpStatus{pb.StatusCode_Ok, ""}, nil}, nil
}

// Server version
func (s *TruthServer) Version(ctx context.Context, in *pb.Request) (*pb.VersionResponse, error) {
  glog.Infof("Version (%v, %v)", ctx, in)
  return &pb.VersionResponse{&pb.OpStatus{pb.StatusCode_Ok, ""}, cfg.VERSION}, nil
}

// Find peer by peer identifier
func (s *TruthServer) FindPeerWithID(ctx context.Context, in *pb.FindPeerRequest) (*pb.Peer, error) {
  glog.Infof("FindPeerWithID (%v, %v)", ctx, in)
  return &pb.Peer{}, nil
}

// Find peer by peer name
func (s *TruthServer) FindPeerWithName(ctx context.Context, in *pb.FindPeerRequest) (*pb.Peer, error) {
  glog.Infof("FindPeerWithName (%v, %v)", ctx, in)
  return &pb.Peer{}, nil
}

// Send a message
func (s *TruthServer) SendMessage(ctx context.Context, in *pb.Message) (*pb.OpStatus, error) {
  glog.Infof("SendMessage (%v, %v)", ctx, in)
  return &pb.OpStatus{pb.StatusCode_Ok, ""}, nil
}

// List unread messages of peer
func (s *TruthServer) ListUnreadMessage(ctx context.Context, in *pb.Request) (*pb.MessageResponse, error){
  glog.Infof("ListUnreadMessage (%v, %v)", ctx, in)
  return &pb.MessageResponse{&pb.OpStatus{pb.StatusCode_Ok, ""}, nil}, nil
}
