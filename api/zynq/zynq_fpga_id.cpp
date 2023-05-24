#include "hw_api.h"
#include "zynq_fpga_id.h"

ZYNQFPGAID::ZYNQFPGAID():FPGAID() {}

void
ZYNQFPGAID::getBuildTime(ZYNQFPGAIDType::BuildTime * build_time) {
    uint32_t reg_data = FPGAID::getBuildStamp();
    build_time->year   = (reg_data >> 17 & 0x3f)+2000;
    build_time->month  = reg_data >> 23 & 0xf;
    build_time->day    = reg_data >> 27 & 0x1f;
    build_time->hour   = reg_data >> 12 & 0x1f;
    build_time->minute = reg_data >>  6 & 0x3f;
    build_time->second = reg_data >>  0 & 0x3f;
    return;
}

void
ZYNQFPGAID::writeFPGAID(uint32_t reg, uint32_t data) {
    HW_API::writeFPGAIDReg(reg, data);
    return;
}

uint32_t
ZYNQFPGAID::readFPGAID(uint32_t reg) {
    return HW_API::readFPGAIDReg(reg);
}
