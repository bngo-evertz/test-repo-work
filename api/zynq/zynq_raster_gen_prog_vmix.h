#ifndef ZYNQ_RASTER_GEN_PROG_VMIX
#define ZYNQ_RASTER_GEN_PROG_VMIX

#include <stdint.h>

#include "raster_gen_prog.h"

class ZYNQRasterGenProgVMix: public RasterGenProg
{
  public:
    ZYNQRasterGenProgVMix();
    ~ZYNQRasterGenProgVMix(){}
    void localInit();
  private:
    void writeRasterGen(uint32_t address, uint32_t data);
    uint32_t readRasterGen(uint32_t address);
    bool m_localInitDone;
    uint32_t m_scalerPath;
};

#endif // ZYNQ_RASTER_GEN_PROG_VMIX
