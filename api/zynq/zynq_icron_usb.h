#ifndef ZYNQ_ICRON_USB_H
#define ZYNQ_ICRON_USB_H

#include "icron_usb.h"

// Constant Definitions
static const uint32_t NUM_IP_PAIRS = 1;

class ZYNQUsbIPUDPIP : public usb_udpip_encap
{
  public:
    ZYNQUsbIPUDPIP();
    ~ZYNQUsbIPUDPIP(){}
  private:
    void writereg(uint32_t address, uint32_t data);
};

// Class Definition
class ZYNQIcronUSB : public IcronUSB
{

  public:

    ZYNQIcronUSB();
    virtual ~ZYNQIcronUSB() {}

    // -- Implementation Specific Methods --

    // Initialize the control software (mandatory, do this first!)
    void init(usb_udpip_encap* encap[IcronUsbConsts::MAX_NUM_IP_PAIRS*2]);

    // Get Init Done
    bool getInitDone();

    // Sleep
    void sleepIcronUSB(uint64_t ns);

    // Lock
    void lockIcronUSB(bool lock);

  private:

    // -- Implementation Specific Methods --

    void writereg(uint32_t addr, uint32_t data);
    uint32_t readreg(uint32_t addr);
    int lockreg(bool lock);

    // -- Internal Data Members

    bool     m_localInitDone;

};

#endif //ZYNQ_ICRON_USB_H
