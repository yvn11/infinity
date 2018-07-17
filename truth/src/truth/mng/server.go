// management service over rpc
package management

import (
  "log"
  "syscall"

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

func (c *TruthManagementServer) SysInfo(ctx context.Context, in *pb.Request) (*pb.SysinfoResponse, error) {
  log.Printf("SysInfo (%v, %v)", ctx, in)
  var ret syscall.Sysinfo_t

  if err := syscall.Sysinfo(&ret); err != nil {
    log.Println("syscall.Sysinfo failed", err)
    return &pb.SysinfoResponse{&pb.OpStatus{
      pb.StatusCode_ServerException, ""}, nil}, err
  }

  return &pb.SysinfoResponse{
    &pb.OpStatus{pb.StatusCode_Ok, ""},
    &pb.Sysinfo{
      Uptime: ret.Uptime,
      Load1: ret.Loads[0],
      Load5: ret.Loads[1],
      Load15: ret.Loads[2],
      Totalram: ret.Totalram,
      Freeram: ret.Freeram,
      Sharedram: ret.Sharedram,
      Bufferram: ret.Bufferram,
      Totalswap: ret.Totalswap,
      Freeswap: ret.Freeswap,
      Procs: uint32(ret.Procs),
      Pad: uint32(ret.Pad),
      Totalhigh: ret.Totalhigh,
      Freehigh: ret.Freehigh,
      Unit: ret.Unit,
    }}, nil
}
