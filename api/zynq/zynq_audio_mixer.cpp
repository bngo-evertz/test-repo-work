#include <assert.h>
#include <stdio.h>

#include "hw_api.h"
#include "zynq_audio_mixer.h"

ZYNQ_Audio_Mixer::ZYNQ_Audio_Mixer():Audio_Mixer(){
  m_localInitDone = false;
  m_index = 0;
}

void
ZYNQ_Audio_Mixer::init(uint32_t index, uint8_t InBits, uint8_t FlBits){
  m_index = index;
  m_localInitDone = true; 
  Audio_Mixer::init(InBits, FlBits);
  return;
}

bool
ZYNQ_Audio_Mixer::getInitDone(){
  return(Audio_Mixer::getInitDone() && m_localInitDone);
}

void
ZYNQ_Audio_Mixer::writereg(uint32_t reg, uint32_t data){
  assert(m_localInitDone);
  HW_API::writeAudioMixerReg(m_index, reg, data);
  return;
}

uint32_t 
ZYNQ_Audio_Mixer::readreg(uint32_t reg){
  assert(m_localInitDone);
  return HW_API::readAudioMixerReg(m_index, reg);
}
