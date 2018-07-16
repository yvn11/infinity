# Truth Makefile

MKDIR		:= mkdir -p
RM			:= rm -rf
BUILD		:= build
PROTOC	:= protoc
GO_PROTO_OUT	:= src/truth_pb
PROTO_PATH		:= protos
GOPATH	:= $(shell pwd)

.PHONY: proto truth clean truth_server truth_client

all: truth

proto:
	$(MKDIR) $(GO_PROTO_OUT)
	$(PROTOC) -I $(PROTO_PATH) --go_out=plugins=grpc:$(GO_PROTO_OUT) $(PROTO_PATH)/*.proto

truth: dependency public_service public_client mng_service mng_client

dependency:
	@echo resolving dependency
	#./scripts/build_dep.sh

public_service: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/public $(GOPATH)/src/truth/public_service/main.go

public_client: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/public_client $(GOPATH)/src/truth/public_client/main.go

mng_service: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/management $(GOPATH)/src/truth/management_service/main.go

mng_client: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/management_client $(GOPATH)/src/truth/management_client/main.go

clean:
	$(RM) $(BUILD)
