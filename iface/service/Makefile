# Algo service makefile
#
INCLUDES	:= ..
CXXFLAGS	:= -Wall -std=c++11 $(INCLUDES:%=-I%)
LIBPATH		:= 
LIBS			:= protobuf grpc++
LDFLAGS		:= $(LIBPATH:%=-L%) $(LIBS:%=-l%)
SRCS			:= $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*.cc)

service: $(SRCS)
	mkdir -p ../build
	g++ $^ $(CXXFLAGS) $(LDFLAGS) -o ../build/$@
