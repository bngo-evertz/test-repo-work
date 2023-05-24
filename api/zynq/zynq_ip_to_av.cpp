#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "zynq_ip_to_av.h"
#include "hw_api.h"

ZYNQIPtoAV::ZYNQIPtoAV( const uint32_t N_VID_ASPENTICO,
                        const uint32_t N_VID_SMPTE2110,
                        const uint32_t N_AUD,
                        const uint32_t N_AUD_CH,
                        const uint32_t N_META,
                        const uint32_t N_USB,
                        const uint32_t N_LOWRATE,
                        const uint32_t N_IP_PAIRS) : IPtoAV(N_VID_ASPENTICO, N_VID_SMPTE2110, N_AUD, N_AUD_CH, N_META, N_USB, N_LOWRATE, N_IP_PAIRS) {

}


void ZYNQIPtoAV::writeIPtoAV(uint32_t address, uint64_t data){
  HW_API::writeXGERxReg(address, data);
  return;
}

uint64_t ZYNQIPtoAV::readIPtoAV(uint32_t address){
  return HW_API::readXGERxReg(address);
}

int ZYNQIPtoAV::lockIPtoAV(bool lock){
  return HW_API::lockXGERxReg(lock);
}

ZYNQIPtoTICO::ZYNQIPtoTICO(const uint32_t N_VID_TICO,
                           const uint32_t CORE_CLK_FREQ_HZ,
                           const uint32_t PIXELS_PER_CLOCK,
                           const uint32_t BITS_PER_PIXEL): IPtoTICO(N_VID_TICO, CORE_CLK_FREQ_HZ, PIXELS_PER_CLOCK, BITS_PER_PIXEL) {
}

void ZYNQIPtoTICO::writeIPtoTICO(uint32_t address, uint64_t data) {
  HW_API::writeXGERxReg(address, data);
    return;
}

uint64_t ZYNQIPtoTICO::readIPtoTICO(uint32_t address) {
  return HW_API::readXGERxReg(address);
}

int ZYNQIPtoTICO::lockIPtoTICO(bool lock) {
  return HW_API::lockXGERxReg(lock);
}
