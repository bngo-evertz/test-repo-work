#ifndef ZYNQ_VID_SCALE_H
#define ZYNQ_VID_SCALE_H

#include <stdint.h>

#include "mv_scaler_top.h"

class ZYNQVidScale : public MVScalerTop
{
  public:
    ZYNQVidScale();
    ~ZYNQVidScale(){}
    void localInit(uint32_t path, uint32_t type);
  private:
    void writeMVScaler(uint32_t address, uint64_t data);
    void writeMVScalerBlock(uint32_t address, uint32_t address_end, uint64_t * data);
    void writeMVScalerBlock(uint32_t address, uint32_t address_end, uint32_t * data_ptr, const uint32_t reg_split);
    void dmaWriteMVScalerBlock(uint32_t address, uint32_t address_end, void * data_ptr, uint32_t dma_chunk_size);
    uint64_t readMVScaler(uint32_t address);
    int lockMVScaler(bool lock);
    bool m_localInitDone;
    uint32_t m_scalerType;
    uint32_t m_scalerPath;
    uint32_t m_lastDMAChunkSize;
};

#endif // ZYNQ_VID_SCALE

// vim:set sts=2 sw=2 expandtab fileformat=unix:
