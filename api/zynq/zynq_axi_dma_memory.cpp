#include <assert.h>
#include <stdio.h>

#include "zynq_axi_dma_memory.h"
#include "hw_api.h"

ZYNQAxiDmaMemory::ZYNQAxiDmaMemory(): AxiDmaMemory(){
  m_localInitDone = false;
}

void
ZYNQAxiDmaMemory::init(uint32_t index) {
  AxiDmaMemory::init();
  m_index = index;
  m_localInitDone = true;
  return;
}

bool
ZYNQAxiDmaMemory::getInitDone() {
  return(AxiDmaMemory::getInitDone() && m_localInitDone);
}

void
ZYNQAxiDmaMemory::writeAxiDmaIpReg(uint32_t reg, uint32_t data) {
  HW_API::writeAxiDmaIpReg(m_index, reg, data);
  return;
}

uint32_t
ZYNQAxiDmaMemory::readAxiDmaIpReg(uint32_t reg) {
  return HW_API::readAxiDmaIpReg(m_index, reg);
}

void
ZYNQAxiDmaMemory::writeAxiDmaMemReg(uint32_t reg, uint32_t data) {
  HW_API::writeAxiDmaMemReg(m_index, reg, data);
  return;
}

uint32_t
ZYNQAxiDmaMemory::readAxiDmaMemReg(uint32_t reg) {
  return HW_API::readAxiDmaMemReg(m_index, reg);
}
