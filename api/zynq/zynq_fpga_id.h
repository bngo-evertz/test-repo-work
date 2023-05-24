#ifndef ZYNQ_FPGA_ID_H
#define ZYNQ_FPGA_ID_H

#include "fpga_id.h"

// Useful Types
namespace ZYNQFPGAIDType {
    typedef struct s_BuildTime {
        uint32_t year;
        uint32_t month;
        uint32_t day;
        uint32_t hour;
        uint32_t minute;
        uint32_t second;
    } BuildTime;
}

// Class Definition
class ZYNQFPGAID : public FPGAID
{

    public:

        ZYNQFPGAID();
        virtual ~ZYNQFPGAID() {}

        // -- Implementation Specific Methods --
        void getBuildTime(ZYNQFPGAIDType::BuildTime * build_time);


    private:

        // -- Implementation Specific Methods --

        void writeFPGAID(uint32_t reg, uint32_t data);
        uint32_t readFPGAID(uint32_t reg);

};

#endif //ZYNQ_FPGA_ID_H
