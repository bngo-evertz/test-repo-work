#ifndef ZYNQ_X7DRP_GTXCH_H
#define ZYNQ_X7DRP_GTXCH_H

#include "x7drp_gtxch.h"

class ZYNQXGEDRP : public X7GTXChannelDRP
{
    public:
        ZYNQXGEDRP();
        ~ZYNQXGEDRP(){}
        void init(uint32_t idx);
        bool getInitDone();
    private:
        void writeDRP(uint32_t address, uint32_t data);
        uint32_t readDRP(uint32_t address);
        int lockDRP(bool lock);
        void waitDRP(uint64_t time_ns);

        bool m_initDone;
        uint32_t m_idx;
};

#endif //ZYNQ_X7DRP_GTXCH_H
