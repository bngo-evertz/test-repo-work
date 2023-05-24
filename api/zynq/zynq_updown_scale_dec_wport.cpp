#include <assert.h>

#include "zynq_updown_scale_dec_wport.h"
#include "hw_api.h"

ZYNQUpDownScaleDecWport::ZYNQUpDownScaleDecWport(): UpDownScaleDecWport() {
    m_localInitDone = false;
    m_scalerPath = 0;
    m_scalerTile = 0;
}

void
ZYNQUpDownScaleDecWport::localInit(uint32_t path, uint32_t tile) {
    m_scalerPath = path;
    m_scalerTile = tile;
    m_localInitDone = true;
    return;
}

void
ZYNQUpDownScaleDecWport::writeUpDownScaleDecWport(uint32_t reg, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeScalerDecWritePortReg(m_scalerPath, m_scalerTile, reg, data);
    return;
}

uint32_t
ZYNQUpDownScaleDecWport::readUpDownScaleDecWport(uint32_t reg) {
    assert(m_localInitDone);
    return HW_API::readScalerDecWritePortReg(m_scalerPath, m_scalerTile, reg);
}

void
ZYNQUpDownScaleDecWport::sleepUpDownScaleDecWport(uint64_t ns) {
    HW_API::hwSleep(ns);
    return;
}

void
ZYNQUpDownScaleDecWport::lockUpDownScaleDecWport(bool lock) {
    assert(m_localInitDone);
    HW_API::lockScalerDecWritePortReg(m_scalerPath, lock);
    return;
}
