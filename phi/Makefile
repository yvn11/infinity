# Phi Makefile
#

GOPATH	:= $(shell pwd)
MKDIR		:= mkdir -p
GO			:= go
BUILD		:= build

.PHONY: producer consumer

all: $(BUILD) producer consumer

$(BUILD):
	$(MKDIR) $@

producer: src/phi/producer.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^

consumer: src/phi/consumer.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^

click_producer: src/phi/apps/clickstream/main.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^

apiserver: src/phi/apps/apiserver/main.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^

checkin_producer: src/phi/apps/userprofile/main.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^
