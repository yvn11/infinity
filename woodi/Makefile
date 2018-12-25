# Woodi Makefile
#

GOPATH	:= $(shell pwd)
MKDIR		:= mkdir -p
GO			:= go
BUILD		:= build

.PHONY: producer consumer

all: $(BUILD) producer consumer

$(BUILD):
	$(MKDIR) $@

producer: src/woodi/producer.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^

consumer: src/woodi/consumer.go
	GOPATH=$(GOPATH) $(GO) build -o $(BUILD)/$@ $^
