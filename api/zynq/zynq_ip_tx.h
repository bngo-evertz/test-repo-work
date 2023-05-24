#ifndef ZYNQ_IP_TX_H
#define ZYNQ_IP_TX_H
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "ip_tx.h"
#include "iptx_udpip_encap.h"

class ZYNQIPTxUDPIP : public iptx_udpip_encap
{
  public:
    ZYNQIPTxUDPIP();
    ~ZYNQIPTxUDPIP(){}
  private:
    void writeIPTx(uint32_t address, uint32_t data);
    uint32_t readIPTx(uint32_t address);
};

class ZYNQIPTx : public IPTx
{
  public:
    ZYNQIPTx(const uint32_t N_XGE,
            const uint32_t N_CHANNELS);
    ~ZYNQIPTx(){}
  private:
    void writeIPTx(uint32_t address, uint32_t data);
    uint32_t readIPTx(uint32_t address);
    int lockIPTx(bool lock);
};

#endif //ZYNQ_IP_TX_H
