#ifndef ZYNQ_RASTER_GEN_PROG
#define ZYNQ_RASTER_GEN_PROG

#include <stdint.h>

#include "raster_gen_prog.h"

class ZYNQRasterGenProg: public RasterGenProg
{
  public:
    ZYNQRasterGenProg();
    ~ZYNQRasterGenProg(){}
    void localInit(uint32_t path);
  private:
    void writeRasterGen(uint32_t address, uint32_t data);
    uint32_t readRasterGen(uint32_t address);
    bool m_localInitDone;
    uint32_t m_scalerPath;
};

#endif // ZYNQ_RASTER_GEN_PROG
