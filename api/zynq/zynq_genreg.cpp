#include "hw_api.h"
#include "zynq_genreg.h"
#include <stdio.h>

ZYNQGENDCXO::ZYNQGENDCXO() {}

void
ZYNQGENDCXO::writereg(uint32_t addr, uint32_t data) {
    HW_API::writeGeneralReg(addr, data);
    return;
}

uint32_t
ZYNQGENDCXO::readreg(uint32_t addr) {
    return HW_API::readGeneralReg(addr);
}

ZYNQGENREG::ZYNQGENREG():GeneralReg() {}

uint32_t
ZYNQGENREG::readreg( uint32_t reg) {
  return HW_API::readGeneralReg(reg);
}

void ZYNQGENREG::writereg(uint32_t reg, uint32_t data) {
  HW_API::writeGeneralReg(reg, data);
}
