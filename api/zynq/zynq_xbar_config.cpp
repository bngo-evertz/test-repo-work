#include "hw_api.h"
#include "zynq_xbar_config.h"
#include <stdio.h>

ZYNQXBARCONFIG::ZYNQXBARCONFIG(const uint32_t N_AUD_XBAR_IN,
                               const uint32_t N_AUD_XBAR_OUT,
                               const uint32_t N_VID_XBAR_IN,
                               const uint32_t N_VID_XBAR_OUT,
                               const uint32_t N_META_XBAR_IN,
                               const uint32_t N_META_XBAR_OUT,
                               const uint32_t THRESH_WIDTH,
                               const uint32_t UNDER_DUR_WIDTH,
                               const uint32_t UNDER_THRESH,
                               const uint32_t UNDER_DURATION):XBARCONFIG(N_AUD_XBAR_IN, N_AUD_XBAR_OUT,
                                                                         N_VID_XBAR_IN, N_VID_XBAR_OUT,
                                                                         N_META_XBAR_IN, N_META_XBAR_OUT,
                                                                         THRESH_WIDTH, UNDER_DUR_WIDTH,
                                                                         UNDER_THRESH, UNDER_DURATION) {}

uint32_t
ZYNQXBARCONFIG::readXBARCONFIG(uint32_t reg) {
  return HW_API::readXBARCONFIGReg(reg);
}

void ZYNQXBARCONFIG::writeXBARCONFIG(uint32_t reg, uint32_t data) {
  HW_API::writeXBARCONFIGReg(reg, data);
}
