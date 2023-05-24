#include <assert.h>
#include <stdio.h>

#include "hw_api.h"
#include "zynq_icron_usb.h"

ZYNQUsbIPUDPIP::ZYNQUsbIPUDPIP() {
}

void
ZYNQUsbIPUDPIP::writereg(uint32_t address, uint32_t data) {
  HW_API::writeIcronUSBReg(address, data);
    return;
}

ZYNQIcronUSB::ZYNQIcronUSB():IcronUSB()
{
    m_localInitDone = false;
}

void
ZYNQIcronUSB::init(usb_udpip_encap* encap[IcronUsbConsts::MAX_NUM_IP_PAIRS*2]) {
    // Set local init flag (do this after all local init)
    m_localInitDone = true;
    // Call parent init function (do this last!)
    IcronUSB::init(1, encap);
    return;
}

bool
ZYNQIcronUSB::getInitDone() {
    return (IcronUSB::getInitDone() && m_localInitDone);
}

void
ZYNQIcronUSB::writereg(uint32_t addr, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeIcronUSBReg(addr, data);
    return;
}

uint32_t
ZYNQIcronUSB::readreg(uint32_t addr) {
    assert(m_localInitDone);
    return HW_API::readIcronUSBReg(addr);
}

void
ZYNQIcronUSB::sleepIcronUSB(uint64_t ns) {
    HW_API::hwSleep(ns);
    return;
}

int
ZYNQIcronUSB::lockreg(bool lock) {
    return HW_API::lockIcronUSBReg(lock);
}
