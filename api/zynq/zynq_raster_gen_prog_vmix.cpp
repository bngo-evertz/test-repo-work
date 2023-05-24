#include <assert.h>
#include <stdio.h>

#include "hw_api.h"
#include "zynq_raster_gen_prog_vmix.h"
#include "video_processing_wrapper_reg.h"

/* -- Hidden helper Functions -- */

#define CLEANSET(result, value, low_bit, high_bit)              \
  do {\
    result &= (uint32_t)~(((1<<(high_bit+1-low_bit))-1)<<low_bit);\
    result |= ((value) & ((1<<(high_bit+1-low_bit))-1))<<low_bit;\
  } while(0)

#define CLEANGET(result, input, low_bit, high_bit) \
  do {\
    result = (input) >> low_bit;\
    result &= ((1<<(high_bit+1-low_bit))-1);\
  } while(0)


ZYNQRasterGenProgVMix::ZYNQRasterGenProgVMix(): RasterGenProg(1){
    m_localInitDone = false;
}

void
ZYNQRasterGenProgVMix::localInit() {
    m_localInitDone = true;
    return;
}

void
ZYNQRasterGenProgVMix::writeRasterGen(uint32_t address, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeVidProcReg(VideoProcessingWrapperReg::REG_RASTER_WADDR,address);
    HW_API::writeVidProcReg(VideoProcessingWrapperReg::REG_RASTER_WDATA,data);
    uint32_t reg = 0;
    CLEANSET(reg, 1, VideoProcessingWrapperReg::RANGE_RASTER_WREQ, VideoProcessingWrapperReg::RANGE_RASTER_WREQ);
    HW_API::writeVidProcReg(VideoProcessingWrapperReg::REG_RASTER_CTRL,reg);
    return;
}

uint32_t
ZYNQRasterGenProgVMix::readRasterGen(uint32_t address) {
    assert(m_localInitDone);
    HW_API::writeVidProcReg(VideoProcessingWrapperReg::REG_RASTER_RADDR,address);
    uint32_t reg = 0;
    CLEANSET(reg, 1, VideoProcessingWrapperReg::RANGE_RASTER_RREQ, VideoProcessingWrapperReg::RANGE_RASTER_RREQ);
    HW_API::writeVidProcReg(VideoProcessingWrapperReg::REG_RASTER_CTRL,reg);
    for(int i=0;i<10;i++) asm("nop");
    return HW_API::readVidProcReg(VideoProcessingWrapperReg::REG_RASTER_RDATA);
}
