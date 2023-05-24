#include <assert.h>
#include <stdio.h>

#include "zynq_updown_scale_wrapper.h"
#include "hw_api.h"

const uint32_t PARAM_MIXER_ALPHA_WIDTH   = 16;

ZYNQUpDownScaleWrapper::ZYNQUpDownScaleWrapper(): UpDownScaleWrapper(PARAM_MIXER_ALPHA_WIDTH
                                                                     ) {
    m_localInitDone = false;
    m_scalerPath = 0;
}

void
ZYNQUpDownScaleWrapper::localInit(uint32_t path) {
    m_scalerPath = path;
    m_localInitDone = true;
    return;
}

void
ZYNQUpDownScaleWrapper::writeUpDownScaleWrapper(uint32_t reg, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeScaleMiscReg(m_scalerPath, reg, data);
    return;
}

uint32_t
ZYNQUpDownScaleWrapper::readUpDownScaleWrapper(uint32_t reg) {
    assert(m_localInitDone);
    return HW_API::readScaleMiscReg(m_scalerPath, reg);
}

void
ZYNQUpDownScaleWrapper::sleepUpDownScaleWrapper(uint64_t ns) {
    assert(m_localInitDone);
    HW_API::hwSleep(ns);
    return;
}

void
ZYNQUpDownScaleWrapper::lockUpDownScaleWrapper(bool lock) {
    assert(m_localInitDone);
    HW_API::lockScaleMiscReg(m_scalerPath, lock);
    return;
}
