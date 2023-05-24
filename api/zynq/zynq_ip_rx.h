#ifndef ZYNQ_IPRX_H
#define ZYNQ_IPRX_H
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "ip_rx.h"

class ZYNQIPRx : public IPRx
{
  public:
    ZYNQIPRx(const uint32_t N_XGE,
             const uint32_t N_CHANNELS,
             const uint32_t IP_CAM_DEPTH);
    ~ZYNQIPRx(){}
  private:
    void writeIPRx(uint32_t address, uint32_t data);
    uint32_t readIPRx(uint32_t address);
    int lockIPRx(bool lock);
};

#endif //ZYNQ_IPRX_H
