#include "hw_api.h"
#include "zynq_interfpga.h"

ZYNQInterfpga::ZYNQInterfpga():Interfpga() {
  m_localInitDone = false;
  m_index = 0;
}

void
ZYNQInterfpga::init(uint8_t index){
  m_index = index;
  m_localInitDone = true; 
  Interfpga::init();
  return;
}

bool
ZYNQInterfpga::getInitDone(){
  return(Interfpga::getInitDone() && m_localInitDone);
}

void
ZYNQInterfpga::writeInterfpga(uint32_t reg, uint32_t data) {
  assert(m_localInitDone);
  HW_API::writeInterfpgaReg(m_index, reg, data);
  return;
}

uint32_t
ZYNQInterfpga::readInterfpga(uint32_t reg) {
  assert(m_localInitDone);
  return HW_API::readInterfpgaReg(m_index, reg);
}
