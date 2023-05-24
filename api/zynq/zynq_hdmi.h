#ifndef ZYNQ_HDMI_H
#define ZYNQ_HDMI_H

#include <stdint.h>

#include "hdmi_xil.h"

class ZYNQHDMI : public HDMI_Xil
{
  public:
    ZYNQHDMI(int baseaddr);
    ~ZYNQHDMI();

    void write(uint32_t addr, uint8_t data) {((uint8_t*)Config)[addr] = data;}
    uint8_t read(uint32_t addr) {return ((uint8_t*)Config)[addr];}
    void loopbackMode(uint8_t mode);
  private:
    int fd;
};

#endif // ZYNQ_HDMI

// vim:set sts=2 sw=2 expandtab fileformat=unix:
