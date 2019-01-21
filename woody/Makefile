# Woody Makefile
#

GOPATH	:= $(shell pwd)
MKDIR		:= mkdir -p
GO			:= go
BUILD		:= build

.PHONY: producer consumer

all: $(BUILD) producer consumer

$(BUILD):
	$(MKDIR) $@

producer: src/woody/producer.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^

consumer: src/woody/consumer.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^

click_producer: src/woody/apps/clickstream/main.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^

click_apiserver: src/woody/apps/clickstream_api/main.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^
