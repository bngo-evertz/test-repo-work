#include <assert.h>
#include <stdio.h>

#include "zynq_raster_gen_prog.h"
#include "hw_api.h"

ZYNQRasterGenProg::ZYNQRasterGenProg(): RasterGenProg(3){
    m_localInitDone = false;
    m_scalerPath = 0;
}

void
ZYNQRasterGenProg::localInit(uint32_t path) {
    m_scalerPath = path;
    m_localInitDone = true;
    return;
}

void
ZYNQRasterGenProg::writeRasterGen(uint32_t address, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeScaleRasterReg(m_scalerPath, address, data);
    return;
}

uint32_t
ZYNQRasterGenProg::readRasterGen(uint32_t address) {
    assert(m_localInitDone);
    return HW_API::readScaleRasterReg(m_scalerPath, address);
}
