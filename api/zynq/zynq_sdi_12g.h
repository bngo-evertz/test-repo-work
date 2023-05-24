#ifndef ZYNQ_SDI_12G_H
#define ZYNQ_SDI_12G_H

#include "sdi_12g.h"

class ZYNQSDI12GDCXO : public sdi_12g_dcxo_ctrl
{
  public:
    ZYNQSDI12GDCXO();
    ~ZYNQSDI12GDCXO(){}
  private:
    void writereg(uint32_t addr, uint32_t data);
    uint32_t readreg(uint32_t addr);
};

// Class Definition
class ZYNQSDI12G : public SDI_12G
{

  public:

    ZYNQSDI12G();
    virtual ~ZYNQSDI12G() {}

    // -- Implementation Specific Methods --

    // Initialize the control software (mandatory, do this first!)
    void init(sdi_12g_dcxo_ctrl* dcxo_ctrl[2]);

    // Get Init Done
    bool getInitDone();

    // Sleep
    void sleepSDI12G(uint64_t ns);

    // Lock
    void lockSDI12GReg(bool lock);

  private:

    // -- Implementation Specific Methods --

    void writereg(uint32_t addr, uint32_t data);
    uint32_t readreg(uint32_t addr);
    int lockreg(bool lock);

    // -- Internal Data Members

    bool     m_localInitDone;

};

#endif //ZYNQ_SDI_12G_H
