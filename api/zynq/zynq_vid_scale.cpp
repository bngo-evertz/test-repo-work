#include <assert.h>
#include <stdio.h>

#include "zynq_vid_scale.h"
#include "hw_api.h"

ZYNQVidScale::ZYNQVidScale(): MVScalerTop(){
    m_localInitDone = false;
    m_scalerType = 0;
    m_scalerPath = 0;
    m_lastDMAChunkSize = 0;
}

void
ZYNQVidScale::localInit(uint32_t path, uint32_t type) {
    m_scalerPath = path;
    m_scalerType = type;
    m_localInitDone = true;
    return;
}

void
ZYNQVidScale::writeMVScaler(uint32_t address, uint64_t data) {
    assert(m_localInitDone);
    switch(m_scalerType)
    {
        case 0:
          HW_API::writeScalerAReg(m_scalerPath, address, (uint32_t)data);
          break;
        case 1:
          HW_API::writeScalerBReg(m_scalerPath, address, (uint32_t)data);
          break;
        default:
          break;
    }
    return;
}

void
ZYNQVidScale::writeMVScalerBlock(uint32_t address, uint32_t address_end, uint64_t * data) {
    assert(m_localInitDone);
    switch(m_scalerType)
    {
        case 0:
            for (unsigned addr = 0; addr < address_end; addr++) {
                HW_API::writeScalerAReg(m_scalerPath, address, (uint32_t)(data[addr]));
            }
            break;
        case 1:
            for (unsigned addr = 0; addr < address_end; addr++) {
                HW_API::writeScalerBReg(m_scalerPath, address, (uint32_t)(data[addr]));
            }
            break;
        default:
            break;
    }
    return;
}

void
ZYNQVidScale::writeMVScalerBlock(uint32_t address, uint32_t address_end, uint32_t * data_ptr, const uint32_t reg_split) {
    assert(m_localInitDone);
    uint32_t split_cnt = 0;
    switch(m_scalerType)
    {
        case 0:
            for (unsigned addr = 0; addr < address_end; addr++) {
                HW_API::writeScalerAReg(m_scalerPath, address+split_cnt, (uint32_t)(data_ptr[addr]));
                if (split_cnt < reg_split-1) {
                    split_cnt++;
                } else {
                    split_cnt = 0;
                }
            }
            break;
        case 1:
            for (unsigned addr = 0; addr < address_end; addr++) {
                HW_API::writeScalerBReg(m_scalerPath, address+split_cnt, (uint32_t)(data_ptr[addr]));
                if (split_cnt < reg_split-1) {
                    split_cnt++;
                } else {
                    split_cnt = 0;
                }
            }
            break;
        default:
            break;
    }
    return;
}

void
ZYNQVidScale::dmaWriteMVScalerBlock(uint32_t address, uint32_t address_end, void * data_ptr, uint32_t dma_chunk_size) {
    assert(m_localInitDone);
    uint64_t * data = (uint64_t *)data_ptr;
    switch(m_scalerType)
    {
        case 0:
            for (unsigned addr = 0; addr < address_end; addr++) {
                HW_API::writeScalerAReg(m_scalerPath, address, (uint32_t)(data[addr]));
            }
            break;
        case 1:
            for (unsigned addr = 0; addr < address_end; addr++) {
                HW_API::writeScalerBReg(m_scalerPath, address, (uint32_t)(data[addr]));
            }
            break;
        default:
            break;
    }
    m_lastDMAChunkSize = dma_chunk_size;
    return;
}

uint64_t
ZYNQVidScale::readMVScaler(uint32_t address) {
    assert(m_localInitDone);
    uint64_t rdata;
    switch(m_scalerType)
    {
        case 0:
          rdata = (uint64_t)HW_API::readScalerAReg(m_scalerPath, address);
          break;
        case 1:
          rdata = (uint64_t)HW_API::readScalerBReg(m_scalerPath, address);
          break;
        default:
          rdata = 0;
          break;
    }
    rdata &= 0xffffffff;
    return rdata;
}

int
ZYNQVidScale::lockMVScaler(bool lock) {
    assert(m_localInitDone);
    switch(m_scalerType)
    {
        case 0:
          return HW_API::lockScalerAReg(m_scalerPath, lock);
          break;
        case 1:
          return HW_API::lockScalerBReg(m_scalerPath, lock);
          break;
        default:
          break;
    }
    return -1;
}
