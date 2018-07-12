# Truth Makefile

MKDIR		:= mkdir -p
PROTOC	:= protoc
GO_PROTO_OUT	:= src/truth/iface
PROTO_PATH		:= protos

.PHONY: proto

proto:
	$(MKDIR) $(GO_PROTO_OUT)
	$(PROTOC) -I $(PROTO_PATH) --go_out=plugins=grpc:$(GO_PROTO_OUT) $(PROTO_PATH)/*.proto
