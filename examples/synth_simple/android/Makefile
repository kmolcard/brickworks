ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

NAME := bw_example_synth_simple
SOURCES = ${SOURCES_COMMON} ${ROOT_DIR}/../src/bw_example_synth_simple.c
SYNTH := yes

include ${ROOT_DIR}/../../common/android/android.mk
