#include <assert.h>
#include <stdio.h>

#include "hw_api.h"
#include "zynq_sdi_12g.h"

ZYNQSDI12GDCXO::ZYNQSDI12GDCXO()
{
}

void
ZYNQSDI12GDCXO::writereg(uint32_t addr, uint32_t data) {
    HW_API::writeSDI12GReg(addr, data);
    return;
}

uint32_t
ZYNQSDI12GDCXO::readreg(uint32_t addr) {
    return HW_API::readSDI12GReg(addr);
}



ZYNQSDI12G::ZYNQSDI12G():SDI_12G()
{
    m_localInitDone = false;
}

void
ZYNQSDI12G::init(sdi_12g_dcxo_ctrl* dcxo_ctrl[2]) {
    // Set local init flag (do this after all local init)
    m_localInitDone = true;
    // Call parent init function (do this last!)
    SDI_12G::init(dcxo_ctrl);
    return;
}

bool
ZYNQSDI12G::getInitDone() {
    return (SDI_12G::getInitDone() && m_localInitDone);
}

void
ZYNQSDI12G::writereg(uint32_t addr, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeSDI12GReg(addr, data);
    return;
}

uint32_t
ZYNQSDI12G::readreg(uint32_t addr) {
    assert(m_localInitDone);
    return HW_API::readSDI12GReg(addr);
}

void
ZYNQSDI12G::sleepSDI12G(uint64_t ns) {
    HW_API::hwSleep(ns);
    return;
}

int
ZYNQSDI12G::lockreg(bool lock) {
    return HW_API::lockSDI12GReg(lock);
}
