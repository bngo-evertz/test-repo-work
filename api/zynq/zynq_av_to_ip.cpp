#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "zynq_av_to_ip.h"
#include "hw_api.h"

inline void localWriteAVtoIP(uint32_t address, uint64_t data) {
    HW_API::writeXGETxReg(address, data);
    return;
}

inline uint64_t localReadAVtoIP(uint32_t address) {
    return HW_API::readXGETxReg(address);
}

ZYNQAVtoIP::ZYNQAVtoIP() {
}

void
ZYNQAVtoIP::writeAVtoIP(uint32_t address, uint64_t data) {
    localWriteAVtoIP(address, data);
    return;
}

uint64_t
ZYNQAVtoIP::readAVtoIP(uint32_t address) {
    return localReadAVtoIP(address);
}

int
ZYNQAVtoIP::lockAVtoIP(bool lock) {
    return HW_API::lockXGETxReg(lock);
}

ZYNQTICOtoIP::ZYNQTICOtoIP(const uint32_t N_VID_TICO,
                               const uint32_t BITS_PER_PIXEL): TICOtoIP(N_VID_TICO, BITS_PER_PIXEL) {
}

void
ZYNQTICOtoIP::writeTICOtoIP(uint32_t address, uint64_t data) {
    localWriteAVtoIP(address, data);
    return;
}

uint64_t
ZYNQTICOtoIP::readTICOtoIP(uint32_t address) {
    return localReadAVtoIP(address);
}

int
ZYNQTICOtoIP::lockTICOtoIP(bool lock) {
    return HW_API::lockXGETxReg(lock);
}
