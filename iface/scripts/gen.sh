#!/bin/bash

mkdir -p service/proto go-cli/src/proto java-cli/proto
protoc -I proto \
      --cpp_out=service/proto \
      --go_out=go-cli/src/proto \
      --java_out=java-cli/proto \
      --proto_path=proto proto/param.proto
protoc -I proto \
      --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
      --grpc_out=service/proto \
      --go_out=plugins=grpc:go-cli/src/proto \
      --cpp_out=service/proto \
      --proto_path=proto proto/facial.proto
