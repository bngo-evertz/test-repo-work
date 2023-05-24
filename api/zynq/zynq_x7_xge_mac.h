#ifndef ZYNQ_X7_XGE_MAC_H
#define ZYNQ_X7_XGE_MAC_H

#include "x7_xge_mac.h"

// Useful Types

// Class Definition
class ZYNQX7XGEMac : public X7XGEMac
{

    public:

        ZYNQX7XGEMac();
        virtual ~ZYNQX7XGEMac() {}

        // -- Implementation Specific Methods --

        // Initialize the control software (mandatory, do this first!)
        void init(uint32_t index);

        // Get Init Done
        bool getInitDone();

    private:

        // -- Implementation Specific Methods --

        void writeX7XGEMac(uint32_t reg, uint32_t data);
        uint32_t readX7XGEMac(uint32_t reg);
        void sleepX7XGEMac(uint64_t ns);
        void lockX7XGEMac(bool lock);

        // -- Internal Data Members
        
        bool     m_localInitDone;
        uint32_t m_index;

};

#endif //ZYNQ_X7_XGE_MAC_H
