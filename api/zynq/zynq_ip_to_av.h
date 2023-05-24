#ifndef TRXS_IP_TO_AV_H
#define TRXS_IP_TO_AV_H
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "ip_to_av.h"
#include "ip_to_tico.h"

class ZYNQIPtoAV : public IPtoAV
{
  public:
    ZYNQIPtoAV( const uint32_t N_VID_ASPENTICO,
                const uint32_t N_VID_SMPTE2110,
                const uint32_t N_AUD,
                const uint32_t N_AUD_CH,
                const uint32_t N_META,
                const uint32_t N_USB,
                const uint32_t N_LOWRATE,
                const uint32_t N_IP_PAIRS);
    ~ZYNQIPtoAV(){}
  private:
    void writeIPtoAV(uint32_t address, uint64_t data);
    uint64_t readIPtoAV(uint32_t address);
    int lockIPtoAV(bool lock);
};

class ZYNQIPtoTICO : public IPtoTICO
{
  public:
    ZYNQIPtoTICO(const uint32_t N_VID_TICO,
                 const uint32_t CORE_CLK_FREQ_HZ,
                 const uint32_t PIXELS_PER_CLOCK,
                 const uint32_t BITS_PER_PIXEL);
    ~ZYNQIPtoTICO(){}
  private:
    void writeIPtoTICO(uint32_t address, uint64_t data);
    uint64_t readIPtoTICO(uint32_t address);
    int lockIPtoTICO(bool lock);
};
#endif //TRXS_IP_TO_AV_H
