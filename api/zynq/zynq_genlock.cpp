#include <assert.h>
#include <stdio.h>

#include "hw_api.h"
#include "zynq_genlock.h"

ZYNQGenlock::ZYNQGenlock():Genlock()
{
    m_localInitDone = false;
}

void
ZYNQGenlock::init() {
    // Set local init flag (do this after all local init)
    m_localInitDone = true;
    // Call parent init function (do this last!)
    Genlock::init();
    return;
}

bool
ZYNQGenlock::getInitDone() {
    return (Genlock::getInitDone() && m_localInitDone);
}

void
ZYNQGenlock::writereg(uint32_t addr, uint32_t data) {
    assert(m_localInitDone);
    HW_API::writeGenlockReg(addr, data);
    return;
}

uint32_t
ZYNQGenlock::readreg(uint32_t addr) {
    assert(m_localInitDone);
    return HW_API::readGenlockReg(addr);
}

void
ZYNQGenlock::sleepns(uint64_t ns) {
    HW_API::hwSleep(ns);
    return;
}

int
ZYNQGenlock::lockreg(bool lock) {
    return HW_API::lockGenlockReg(lock);
}
