#ifndef ZYNQ_INTERFPGA_H
#define ZYNQ_INTERFPGA_H

#include "interfpga.h"

// Class Definition
class ZYNQInterfpga : public Interfpga
{
  public:
    ZYNQInterfpga();
    virtual ~ZYNQInterfpga() {}
    //Initialize the control software
    void init(uint8_t quad);
    bool getInitDone();

  private:
    // -- Implementation Specific Methods --
    void writeInterfpga(uint32_t reg, uint32_t data);
    uint32_t readInterfpga(uint32_t reg);

    // -- Internal Data Members
    bool m_localInitDone;
    uint32_t m_index;
};

#endif //ZYNQ_INTERFPGA_H
