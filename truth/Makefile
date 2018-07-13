# Truth Makefile

MKDIR		:= mkdir -p
BUILD		:= build
PROTOC	:= protoc
GO_PROTO_OUT	:= src/truth_pb
PROTO_PATH		:= protos

.PHONY: proto truth

proto:
	$(MKDIR) $(GO_PROTO_OUT)
	$(PROTOC) -I $(PROTO_PATH) --go_out=plugins=grpc:$(GO_PROTO_OUT) $(PROTO_PATH)/*.proto

truth: dependency truth_server truth_client

dependency:
	@echo resolving dependency
	#@ln -s /usr/share/gocode/src/* src/ 2> /dev/null

truth_server: proto
	@cd src/truth/server
	GOPATH=/pri/lab/infinity/truth go build -o $(BUILD)/truth_server

truth_client: proto
	@cd src/truth/client
	GOPATH=/pri/lab/infinity/truth go build -o $(BUILD)/truth_client 
