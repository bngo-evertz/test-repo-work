#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "zynq_ip_tx.h"
#include "hw_api.h"

inline void localWriteIPTx(uint32_t address, uint32_t data) {
    HW_API::writeIPTxReg(address, data);
    return;
}

inline uint32_t localReadIPTx(uint32_t address) {
    return HW_API::readIPTxReg(address);
}

ZYNQIPTxUDPIP::ZYNQIPTxUDPIP() {
}

void
ZYNQIPTxUDPIP::writeIPTx(uint32_t address, uint32_t data) {
    localWriteIPTx(address, data);
    return;
}

uint32_t
ZYNQIPTxUDPIP::readIPTx(uint32_t address) {
    return localReadIPTx(address);
}

ZYNQIPTx::ZYNQIPTx(const uint32_t N_XGE,
                   const uint32_t N_CHANNELS) : IPTx(N_XGE, N_CHANNELS) {
}

void
ZYNQIPTx::writeIPTx(uint32_t address, uint32_t data) {
    localWriteIPTx(address, data);
    return;
}

uint32_t
ZYNQIPTx::readIPTx(uint32_t address) {
    return localReadIPTx(address);
}

int
ZYNQIPTx::lockIPTx(bool lock) {
    return HW_API::lockIPTxReg(lock);
}
