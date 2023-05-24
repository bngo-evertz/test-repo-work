#include <assert.h>

#include "zynq_playout_ctrl.h"
#include "hw_api.h"

ZYNQPlayoutCtrl::ZYNQPlayoutCtrl(): PlayoutCtrl() {
    m_localInitDone = false;
    m_scalerPath = 0;
}

void
ZYNQPlayoutCtrl::localInit(uint32_t path) {
    m_scalerPath = path;
    m_localInitDone = true;
    return;
}

void
ZYNQPlayoutCtrl::writePlayoutCtrl(uint32_t reg, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeScalerPlayoutReg(m_scalerPath, reg, data);
    return;
}

uint32_t
ZYNQPlayoutCtrl::readPlayoutCtrl(uint32_t reg) {
    assert(m_localInitDone);
    return HW_API::readScalerPlayoutReg(m_scalerPath, reg);
}

void
ZYNQPlayoutCtrl::sleepPlayoutCtrl(uint64_t ns) {
    HW_API::hwSleep(ns);
    return;
}

void
ZYNQPlayoutCtrl::lockPlayoutCtrl(bool lock) {
    assert(m_localInitDone);
    HW_API::lockScalerPlayoutReg(m_scalerPath, lock);
    return;
}
