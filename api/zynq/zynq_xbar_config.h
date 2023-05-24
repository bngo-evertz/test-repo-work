#ifndef ZYNQ_XBAR_CONFIG_H
#define ZYNQ_XBAR_CONFIG_H

#include "xbar_config.h"

// Class Definition
class ZYNQXBARCONFIG : public XBARCONFIG
{

    public:

        ZYNQXBARCONFIG(const uint32_t N_AUD_XBAR_IN,
                       const uint32_t N_AUD_XBAR_OUT,
                       const uint32_t N_VID_XBAR_IN,
                       const uint32_t N_VID_XBAR_OUT,
                       const uint32_t N_META_XBAR_IN,
                       const uint32_t N_META_XBAR_OUT,
                       const uint32_t THRESH_WIDTH,
                       const uint32_t UNDER_DUR_WIDTH,
                       const uint32_t UNDER_THRESH,
                       const uint32_t UNDER_DURATION);
        virtual ~ZYNQXBARCONFIG() {}

    private:

        // -- Implementation Specific Methods --

        void writeXBARCONFIG(uint32_t reg, uint32_t data);
        uint32_t readXBARCONFIG(uint32_t reg);

};

#endif //ZYNQ_XBAR_CONFIG_H
