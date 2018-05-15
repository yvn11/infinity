# Makefile for Incredible
# Author: Zex Li <top_zlynch@yahoo.com>

CC 				:= g++
CXXFLAGS 	:= -std=c++17 # -shared
INCLUDES 	:= .
SRC				:= incredible.cpp
BUILD			:= ./build
INCREDIBLE	:= $(BUILD)/incredible
CXXFLAGS 	+= $(INCLUDES:%=-I%)

include makefiles/preset.mk

all: $(BUILD) $(INCREDIBLE)

$(INCREDIBLE): $(SRC)
	$(CC) -o $@ $(CXXFLAGS) $^
