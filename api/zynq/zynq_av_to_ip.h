#ifndef ZYNQ_AV_TO_IP_H
#define ZYNQ_AV_TO_IP_H
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "av_to_ip.h"
#include "tico_to_ip.h"

class ZYNQAVtoIP : public AVtoIP
{
  public:
    ZYNQAVtoIP();
    ~ZYNQAVtoIP(){}
  private:
    void writeAVtoIP(uint32_t address, uint64_t data);
    uint64_t readAVtoIP(uint32_t address);
    int lockAVtoIP(bool lock);
};

class ZYNQTICOtoIP : public TICOtoIP
{
  public:
    ZYNQTICOtoIP(const uint32_t N_VID_TICO,
                   const uint32_t BITS_PER_PIXEL);
    ~ZYNQTICOtoIP(){}
  private:
    void writeTICOtoIP(uint32_t address, uint64_t data);
    uint64_t readTICOtoIP(uint32_t address);
    int lockTICOtoIP(bool lock);
};
#endif //ZYNQ_AV_TO_IP_H
