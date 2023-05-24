#include <assert.h>

#include "zynq_updown_scale_wport.h"
#include "hw_api.h"

ZYNQUpDownScaleWport::ZYNQUpDownScaleWport(): UpDownScaleWport() {
    m_localInitDone = false;
    m_scalerPath = 0;
    m_scalerTile = 0;
}

void
ZYNQUpDownScaleWport::localInit(uint32_t path, uint32_t tile) {
    m_scalerPath = path;
    m_scalerTile = tile;
    m_localInitDone = true;
    return;
}

void
ZYNQUpDownScaleWport::writeUpDownScaleWport(uint32_t reg, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeScalerWritePortReg(m_scalerPath, m_scalerTile, reg, data);
    return;
}

uint32_t
ZYNQUpDownScaleWport::readUpDownScaleWport(uint32_t reg) {
    assert(m_localInitDone);
    return HW_API::readScalerWritePortReg(m_scalerPath, m_scalerTile, reg);
}

void
ZYNQUpDownScaleWport::sleepUpDownScaleWport(uint64_t ns) {
    HW_API::hwSleep(ns);
    return;
}

void
ZYNQUpDownScaleWport::lockUpDownScaleWport(bool lock) {
    assert(m_localInitDone);
    HW_API::lockScalerWritePortReg(m_scalerPath, lock);
    return;
}
