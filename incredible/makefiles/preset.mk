# makefiles - base

BUILD ?= ./build

build:
	@mkdir -p $(BUILD)

clean:
	@rm -rf $(BUILD)
