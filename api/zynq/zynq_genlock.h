#ifndef ZYNQ_GENLOCK_H
#define ZYNQ_GENLOCK_H

#include "genlock.h"

// Class Definition
class ZYNQGenlock : public Genlock
{

  public:

    ZYNQGenlock();
    virtual ~ZYNQGenlock() {}

    // -- Implementation Specific Methods --

    // Initialize the control software (mandatory, do this first!)
    void init();

    // Get Init Done
    bool getInitDone();

    // Lock
    void lockGenlockReg(bool lock);

  private:

    // -- Implementation Specific Methods --

    void writereg(uint32_t addr, uint32_t data);
    uint32_t readreg(uint32_t addr);
    int lockreg(bool lock);
    void sleepns(uint64_t ns);

    // -- Internal Data Members

    bool m_localInitDone;

};

#endif //ZYNQ_GENLOCK_H
