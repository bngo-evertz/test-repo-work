#ifndef ZYNQ_AUDIO_MIXER_H
#define ZYNQ_AUDIO_MIXER_H

#include "audio_mixer.h"
//Class Definition
class ZYNQ_Audio_Mixer : public Audio_Mixer{
  public:
    ZYNQ_Audio_Mixer();
    virtual ~ZYNQ_Audio_Mixer(){}
    //Initialize the control software
    void init(uint32_t index, uint8_t InBits, uint8_t FlBits);
    // Get Init Done
    bool getInitDone(); 

  private:
    // -- Implementation of Specific Methods --
    void writereg(uint32_t reg, uint32_t data);
    uint32_t readreg(uint32_t reg);

    // -- Internal Data Members
    bool m_localInitDone;
    uint32_t m_index;
};
#endif // ZYNQ_AUDIO_MIXER_H
