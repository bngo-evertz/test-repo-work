#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "zynq_ip_rx.h"
#include "hw_api.h"

ZYNQIPRx::ZYNQIPRx(const uint32_t N_XGE,
                   const uint32_t N_CHANNELS,
                   const uint32_t IP_CAM_DEPTH) : IPRx(N_XGE, N_CHANNELS, IP_CAM_DEPTH) {
}


void ZYNQIPRx::writeIPRx(uint32_t address, uint32_t data){
  HW_API::writeIPRxReg(address, data);
  return;
}

uint32_t ZYNQIPRx::readIPRx(uint32_t address){
  return HW_API::readIPRxReg(address);
}

int ZYNQIPRx::lockIPRx(bool lock){
  return HW_API::lockIPRxReg(lock);
}
