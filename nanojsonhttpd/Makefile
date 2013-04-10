#
# Copyright 2012 Sony Corporation. All Rights Reserved.
#

ROOT_DIR ?= ../../..

TARGET_BASE := libWanHttpd.so
TARGET_TYPE := shared

INCLUDE_DIR += \
	../lib \


SRCS := $(filter-out $(EXCLUDE_SRCS), $(wildcard *.cpp))
SRCS += $(filter-out $(EXCLUDE_SRCS), $(wildcard *.c))

LIB_BASE += \
	rt dl pthread \


ifeq ($(OS),Windows_NT)
LIB_BASE += iphlpapi
endif


LDFLAGS += -L../lib/$(PLATFORM)/$(CONFIG) \


CFLAGS += -Wno-write-strings
CXXFLAGS += -Wno-write-strings
CXXFLAGS += -fpermissive

ifeq ($(OS),Windows_NT)
PLATFORM := Linux32
endif


all0: all
ifeq ($(OS),Windows_NT)
	cp -a $(TARGET) $(PLATFORM)/$(CONFIG)/$(subst .so,.dll.a,$(TARGET_BASE))
endif



include $(ROOT_DIR)/Build/Common.mk
