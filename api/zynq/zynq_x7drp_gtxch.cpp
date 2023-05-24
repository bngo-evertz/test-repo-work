#include <assert.h>

#include "zynq_x7drp_gtxch.h"
#include "hw_api.h"

ZYNQXGEDRP::ZYNQXGEDRP(): X7GTXChannelDRP() {
    m_idx = 0;
    m_initDone = false;
}

void
ZYNQXGEDRP::init(uint32_t idx) {
    m_idx = idx;
    X7GTXChannelDRP::init();
    m_initDone = true;
    return;
}

bool
ZYNQXGEDRP::getInitDone() {
    return m_initDone;
}

void
ZYNQXGEDRP::writeDRP(uint32_t address, uint32_t data) {
    assert(m_initDone);
    HW_API::writeXGEDRPReg(m_idx, address, data);
    return;
}

uint32_t
ZYNQXGEDRP::readDRP(uint32_t address) {
    assert(m_initDone);
    return HW_API::readXGEDRPReg(m_idx, address);
}

int
ZYNQXGEDRP::lockDRP(bool lock) {
    assert(m_initDone);
    return HW_API::lockXGEDRPChReg(m_idx, lock);
}

void
ZYNQXGEDRP::waitDRP(uint64_t time_ns) {
    HW_API::hwSleep(time_ns);
    return;
}
