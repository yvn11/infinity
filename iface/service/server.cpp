#include <memory>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "service/algo.h"
#include "service/shared.h"

using service::algo::Facial;

void run_server() {
  Facial facial_svr;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(ALGO_SVR_ADDR, grpc::InsecureServerCredentials());
  builder.RegisterService(&facial_svr);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  log_info("server started");
  server->Wait();
}

int main(int argc, char* argv[]) {
  run_server();
  return 0;
}
