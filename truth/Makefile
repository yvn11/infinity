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

truth: dependency public_service public_client mng_service mng_client rest_service

dependency:
	@echo resolving dependency
	#./scripts/build_dep.sh

public_service: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/public $(GOPATH)/src/truth/public_service/main.go

public_client: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/public_client $(GOPATH)/src/truth/public_client/main.go

mng_service: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/mng $(GOPATH)/src/truth/mng_service/main.go

mng_client: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/mng_client $(GOPATH)/src/truth/mng_client/main.go

rest_service: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/rest_server $(GOPATH)/src/truth/rest_server/main.go

clean:
	$(RM) $(BUILD) $(GO_PROTO_OUT)
