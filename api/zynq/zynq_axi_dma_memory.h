#ifndef ZYNQ_AXI_DMA_MEMORY_H
#define ZYNQ_AXI_DMA_MEMORY_H

#include <stdint.h>

#include "axi_dma_memory.h"

class ZYNQAxiDmaMemory: public AxiDmaMemory
{

    public:

        ZYNQAxiDmaMemory();
        virtual ~ZYNQAxiDmaMemory() {}

        void init(uint32_t index);
        bool getInitDone();

    private:

        // -- Implementation Specific Methods --

        void writeAxiDmaIpReg(uint32_t reg, uint32_t data);
        uint32_t readAxiDmaIpReg(uint32_t reg);

        void writeAxiDmaMemReg(uint32_t reg, uint32_t data);
        uint32_t readAxiDmaMemReg(uint32_t reg);

        // -- Internal Data Members --

        bool m_localInitDone;
        uint32_t m_index;

};

#endif //ZYNQ_AXI_DMA_MEMORY_H
