#ifndef ZYNQ_AXI_10G_INTF_H
#define ZYNQ_AXI_10G_INTF_H

#include "axi_10g_intf.h"

// Class Definition
class ZYNQAXI10GIntf : public AXI10GIntf
{

    public:

        ZYNQAXI10GIntf();
        virtual ~ZYNQAXI10GIntf() {}

        // -- Implementation Specific Methods --

    private:

        // -- Implementation Specific Methods --

        void writeAXI10GIntf(uint32_t reg, uint32_t data);
        uint32_t readAXI10GIntf(uint32_t reg);

};

#endif //ZYNQ_AXI_10G_INTF_H
