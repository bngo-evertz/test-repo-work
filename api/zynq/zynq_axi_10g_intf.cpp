#include "hw_api.h"
#include "zynq_axi_10g_intf.h"

ZYNQAXI10GIntf::ZYNQAXI10GIntf():AXI10GIntf() {}

void
ZYNQAXI10GIntf::writeAXI10GIntf(uint32_t reg, uint32_t data) {
    HW_API::writeXGEIfReg(reg, data);
    return;
}

uint32_t
ZYNQAXI10GIntf::readAXI10GIntf(uint32_t reg) {
    return HW_API::readXGEIfReg(reg);
}
