ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

NAME := bw_example_fx_vibrato
SOURCE := bw_example_fx_vibrato.c

include ${ROOT_DIR}/../../common/vst3/vst3.mk

CXXFLAGS += -DRELEASE=1 -DNDEBUG -DBW_NO_DEBUG
#CXXFLAGS += -DDEVELOPMENT=1 -DBW_DEBUG_DEEP
