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

truth: dependency truth_server truth_client

dependency:
	@echo resolving dependency
	#@ln -s /usr/share/gocode/src/* src/ 2> /dev/null

truth_server: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/server $(GOPATH)/src/truth/server_app/truth.go

truth_client: proto
	GOPATH=$(GOPATH) go build -o $(BUILD)/truth/client $(GOPATH)/src/truth/client/client.go

clean:
	$(RM) $(BUILD)
