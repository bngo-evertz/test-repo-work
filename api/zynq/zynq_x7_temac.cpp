#include <assert.h>
#include <stdio.h>

#include "hw_api.h"
#include "zynq_x7_temac.h"

ZYNQX7TEMAC::ZYNQX7TEMAC():X7TEMAC() {
    m_localInitDone = false;
    m_index = 0;
}

void
ZYNQX7TEMAC::init(uint32_t index) {
    m_index = index;
    // Set local init flag (do this after all local init)
    m_localInitDone = true;
    // Call parent init function (do this last!)
    X7TEMAC::init();
    return;
}

bool
ZYNQX7TEMAC::getInitDone() {
    return (X7TEMAC::getInitDone()&&m_localInitDone);
}

void
ZYNQX7TEMAC::writeX7TEMAC(uint32_t reg, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeTEMACReg(m_index, reg, data);
    return;
}

uint32_t
ZYNQX7TEMAC::readX7TEMAC(uint32_t reg) {
    assert(m_localInitDone);
    return HW_API::readTEMACReg(m_index, reg);
}

void
ZYNQX7TEMAC::sleepX7TEMAC(uint64_t ns) {
    HW_API::hwSleep(ns);
    return;
}

void
ZYNQX7TEMAC::lockX7TEMAC(bool lock) {
    assert(m_localInitDone);
    HW_API::lockXGEMReg(m_index, lock);
    return;
}
