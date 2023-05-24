VIVADO_VER ?= 2016.1
CURR_DIR ?= .
GIT_MODULES = $(CURR_DIR)/../../../git_modules
COMMON_GIT_MODULES = $(GIT_MODULES)/mma/hdl-common/git_modules
include $(COMMON_GIT_MODULES)/fl/util/env.mk

PROG := hw

OBJS :=
VPATH:=

CFLAGS:=
CFLAGS += -DDEBUG_PRINT
#CFLAGS:=-stdc++11

LDADD += -pthread

include ../sources.mk
CFLAGS += $(patsubst %,-I%,$(VPATH))
include rules.mk
