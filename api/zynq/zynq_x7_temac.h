#ifndef ZYNQ_X7_TEMAC_H
#define ZYNQ_X7_TEMAC_H

#include "x7_temac.h"

// Useful Types

// Class Definition
class ZYNQX7TEMAC : public X7TEMAC
{

    public:

        ZYNQX7TEMAC();
        virtual ~ZYNQX7TEMAC() {}

        // -- Implementation Specific Methods --

        // Initialize the control software (mandatory, do this first!)
        void init(uint32_t index);

        // Get Init Done
        bool getInitDone();

    private:

        // -- Implementation Specific Methods --

        void writeX7TEMAC(uint32_t reg, uint32_t data);
        uint32_t readX7TEMAC(uint32_t reg);
        void sleepX7TEMAC(uint64_t ns);
        void lockX7TEMAC(bool lock);

        // -- Internal Data Members
        
        bool     m_localInitDone;
        uint32_t m_index;

};

#endif //ZYNQ_X7_TEMAC_H
