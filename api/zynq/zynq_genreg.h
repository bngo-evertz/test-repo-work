#ifndef ZYNQ_GENREG_H
#define ZYNQ_GENREG_H

#include "general_reg.h"

class ZYNQGENDCXO : public gen_dcxo_ctrl
{
  public:
    ZYNQGENDCXO();
    ~ZYNQGENDCXO(){}
  private:
    void writereg(uint32_t addr, uint32_t data);
    uint32_t readreg(uint32_t addr);
};

// Class Definition
class ZYNQGENREG : public GeneralReg
{

    public:

        ZYNQGENREG();
        virtual ~ZYNQGENREG() {}

    private:

        // -- Implementation Specific Methods --

        void writereg(uint32_t reg, uint32_t data);
        uint32_t readreg(uint32_t reg);
};

#endif //ZYNQ_GENREG_H
