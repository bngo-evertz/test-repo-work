#include <assert.h>
#include <stdio.h>

#include "zynq_video_processing_wrapper.h"
#include "hw_api.h"

const uint32_t PARAM_PIXELS_PER_CLOCK = 4;

ZYNQVideoProcessingWrapper::ZYNQVideoProcessingWrapper(): VideoProcessingWrapper(PARAM_PIXELS_PER_CLOCK){
    m_localInitDone = false;
}

void
ZYNQVideoProcessingWrapper::init(RasterGenProg* vidmix_raster) {
  if (not HW_API::getFPGABuildIDInitDone()){
    HW_API::initFPGABuildID();
  }
  VideoProcessingWrapper::init( HW_API::getFPGACapability("N_SCALER"),
                                HW_API::getFPGACapability("N_FRAME_BUFFER"),
                                HW_API::getFPGACapability("N_PIP_SCALER_PATHS"),
                                HW_API::getFPGACapability("N_VIDPROC_MIXER"),
                                vidmix_raster);
  m_localInitDone = true;
  return;
}

bool
ZYNQVideoProcessingWrapper::getInitDone() {
  return(VideoProcessingWrapper::getInitDone() && m_localInitDone);
}

void
ZYNQVideoProcessingWrapper::writeVideoProcessingWrapper(uint32_t reg, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeVidProcReg(reg, data);
    return;
}

uint32_t
ZYNQVideoProcessingWrapper::readVideoProcessingWrapper(uint32_t reg) {
    assert(m_localInitDone);
    return HW_API::readVidProcReg(reg);
}

