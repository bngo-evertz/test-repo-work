#
# This Makefile is a part of build/Makefile to be included.
#
# It is to include all c/cpp files under this folder to be compiled, and
#       to include all subdirs which contain sources.mak
#
# NOTE: to correctly use this sources.mak, it is very important to initialize
#
#       VPATH :=
#       OBJS  :=
#
#      in the top-level Makefile (usually it is build/Makefile).
#
# TODO: eliminate the same file name under different folder issue.

# current folder of this source.mak (Be aware it is not $PWD)
THIS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# update VPATH.
VPATH += $(THIS_DIR)
# all cpp files.
#OBJS += $(patsubst %.cpp,$(THIS_DIR)%.o,$(subst $(THIS_DIR),,$(wildcard $(THIS_DIR)*.cpp)))
OBJS += $(patsubst %.cpp,%.o,$(subst $(THIS_DIR),,$(wildcard $(THIS_DIR)*.cpp)))
# all c   files.
OBJS += $(patsubst %.c,%.o,$(subst $(THIS_DIR),,$(wildcard $(THIS_DIR)*.c)))

# Useful library code
VPATH += $(COMMON_GIT_MODULES)/libmv/common-include

# XBAR Config Code
VPATH += $(GIT_MODULES)/mma/hdl-common/xbar/api
OBJS += xbar_config.o

# FPGA ID Code
VPATH += $(GIT_MODULES)/mma/hdl-common/fpga_id/api
OBJS += fpga_id.o

# 10GE Mac Code
VPATH += $(COMMON_GIT_MODULES)/fl/x7gt/xge_mac/api
OBJS += x7_xge_mac.o

# TEMAC Code
VPATH += $(COMMON_GIT_MODULES)/fl/x7gt/temac/api
OBJS += x7_temac.o

# 10GE Interface Code
VPATH += $(GIT_MODULES)/mma/hdl-common/ip10g/api
OBJS += axi_10g_intf.o

# 10GE Tx Code
VPATH += $(GIT_MODULES)/mma/hdl-common/ip10g_tx/ip_tx/api
OBJS += ip_tx.o
OBJS += iptx_udpip_encap.o
OBJS += udpip_encap.o
VPATH += $(GIT_MODULES)/mma/hdl-common/ip10g_tx/api
OBJS += av_to_ip.o

# 10GE Rx Code
VPATH += $(GIT_MODULES)/mma/hdl-common/ip10g_rx/api
OBJS += ip_to_av.o
VPATH += $(GIT_MODULES)/mma/hdl-common/ip10g_rx/ip_rx/api
OBJS += ip_rx.o

# Tico
VPATH += $(COMMON_GIT_MODULES)/flts/libts/tico/cpu_config_interface/api
OBJS += tico_cpu_prog.o
VPATH += $(GIT_MODULES)/mma/hdl-common/ip10g_tx/api
OBJS += vid_to_ts_tico.o
OBJS += tico_to_ip.o
VPATH += $(GIT_MODULES)/mma/hdl-common/ip10g_rx/api
OBJS += tico_ts_to_vid.o
OBJS += ip_to_tico.o

# AXI DMA to DDR Code
VPATH += $(GIT_MODULES)/mma/hdl-common/mem/api
OBJS += axi_dma_memory.o
VPATH += $(GIT_MODULES)/mma/hdl-common/video_misc/bitmap_convert
OBJS += bitmap_convert.o

# Memory Test Code
VPATH += $(GIT_MODULES)/mma/hdl-common/mem_test/api
OBJS += mem_test_wrapper.o

# Scaler Wrapper Code
VPATH += $(GIT_MODULES)/mma/hdl-common/scaler/api
OBJS += updown_scale_wrapper.o
OBJS += updown_scale_core.o
OBJS += updown_scale_pre_and_post.o
OBJS += updown_scale_dual_post.o
OBJS += updown_scale_quad_dual_post.o
OBJS += updown_scale_single_post.o
OBJS += updown_scale_single_pre.o
OBJS += updown_scale_wport.o
OBJS += updown_scale_dec_wport.o
OBJS += playout_ctrl.o

# Video Processing Wrapper
VPATH += $(GIT_MODULES)/mma/hdl-common/video_process/api
OBJS += video_processing_wrapper.o

# Scaler Code
VPATH += $(GIT_MODULES)/mma/hdl-common/scaler/multiviewer/scaler/api
OBJS += mv_scaler_top.o

# Raster Code
VPATH += $(COMMON_GIT_MODULES)/libmv/multiviewer/output/raster_gen/raster_gen_prog/api
VPATH += $(COMMON_GIT_MODULES)/libmv/multiviewer/common/raster
OBJS += raster_gen_prog.o
OBJS += raster_gen_calc.o
OBJS += raster_parameters.o

# HDMI Code
VPATH += $(GIT_MODULES)/mma/hdl-common/hdmi/api
OBJS += hdmi_xil.o
OBJS += hdmi_infoframes.o
OBJS += hdmi_calculations.o
OBJS += hdmi_debug.o

# ICRON USB Code
VPATH += $(GIT_MODULES)/mma/hdl-common/usb/api
OBJS += usb_udpip_encap.o
OBJS += icron_usb.o

# 10GE DRP Code
VPATH += $(COMMON_GIT_MODULES)/fl/x7gt/drp/api
OBJS += x7drp_gtxch.o
OBJS += x7drp.o

# Audio Mixer Code
VPATH += $(GIT_MODULES)/mma/hdl-common/audio_mixer/api
OBJS += audio_mixer.o

# InterFPGA Code
VPATH += $(GIT_MODULES)/mma/hdl-common/interfpga/api
OBJS += interfpga.o

# SDI 12G Code
VPATH += $(GIT_MODULES)/mma/hdl-common/sdi_12g/api
VPATH += $(GIT_MODULES)/mma/hdl-common/vidlock/dcxo_i2c_interface/api
OBJS += sdi_12g_dcxo_ctrl.o
OBJS += sdi_12g.o

# DCXO code
VPATH += $(GIT_MODULES)/mma/hdl-common/vidlock/dcxo_i2c_interface/api
OBJS += dcxo_ctrl.o
OBJS += cy29411_ctrl.o
OBJS += si570_ctrl.o

# Genlock Code
VPATH += $(GIT_MODULES)/mma/hdl-common/genlock/api
OBJS += si570.o
OBJS += genlock.o

# include all subdirs which contain sources.mk
include $(wildcard $(THIS_DIR)*/sources.mk)
