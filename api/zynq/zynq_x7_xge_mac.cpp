#include <assert.h>
#include <stdio.h>

#include "hw_api.h"
#include "zynq_x7_xge_mac.h"

ZYNQX7XGEMac::ZYNQX7XGEMac():X7XGEMac() {
    m_localInitDone = false;
    m_index = 0;
}

void
ZYNQX7XGEMac::init(uint32_t index) {
    m_index = index;
    // Set local init flag (do this after all local init)
    m_localInitDone = true;
    // Call parent init function (do this last!)
    X7XGEMac::init();
    return;
}

bool
ZYNQX7XGEMac::getInitDone() {
    return (X7XGEMac::getInitDone()&&m_localInitDone);
}

void
ZYNQX7XGEMac::writeX7XGEMac(uint32_t reg, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeXGEMacReg(m_index, reg, data);
    return;
}

uint32_t
ZYNQX7XGEMac::readX7XGEMac(uint32_t reg) {
    assert(m_localInitDone);
    return HW_API::readXGEMacReg(m_index, reg);
}

void
ZYNQX7XGEMac::sleepX7XGEMac(uint64_t ns) {
    HW_API::hwSleep(ns);
    return;
}

void
ZYNQX7XGEMac::lockX7XGEMac(bool lock) {
    assert(m_localInitDone);
    HW_API::lockXGEMReg(m_index, lock);
    return;
}
