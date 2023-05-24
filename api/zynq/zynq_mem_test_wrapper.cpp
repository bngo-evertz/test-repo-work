#include <assert.h>
#include <stdio.h>

#include "hw_api.h"
#include "zynq_mem_test_wrapper.h"

const uint32_t PARAM_SDRAM_N_A_BITS = 28;
const uint32_t PARAM_SDRAM_WIDTH    = 64;
const uint32_t PARAM_SDRAM_BL       = 8;
const uint32_t PARAM_CTRL_WIDTH     = 512;
const uint32_t PARAM_TEST_MAX_LEN   = 2048;

ZYNQMemTestWrapper::ZYNQMemTestWrapper():MemTestWrapper(PARAM_SDRAM_N_A_BITS,
                                                        PARAM_SDRAM_WIDTH,
                                                        PARAM_SDRAM_BL,
                                                        PARAM_CTRL_WIDTH,
                                                        PARAM_TEST_MAX_LEN
                                                        ) {
    m_localInitDone = false;
    m_memBank = 0;
}

void
ZYNQMemTestWrapper::localInit(uint32_t bank) {
    m_memBank = bank;
    m_localInitDone = true;
    return;
}
void
ZYNQMemTestWrapper::writeMemTestWrapper(uint32_t reg, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeMemTestReg(m_memBank, reg, data);
    return;
}

uint32_t
ZYNQMemTestWrapper::readMemTestWrapper(uint32_t reg) {
    assert(m_localInitDone);
    return HW_API::readMemTestReg(m_memBank, reg);
}

void
ZYNQMemTestWrapper::sleepMemTestWrapper(uint64_t ns) {
    assert(m_localInitDone);
    HW_API::hwSleep(ns);
    return;
}

void
ZYNQMemTestWrapper::lockMemTestWrapper(bool lock) {
    assert(m_localInitDone);
    HW_API::lockMemTestReg(m_memBank, lock);
    return;
}

