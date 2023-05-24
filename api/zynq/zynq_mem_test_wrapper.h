#ifndef ZYNQ_MEM_TEST_WRAPPER_H
#define ZYNQ_MEM_TEST_WRAPPER_H

#include "mem_test_wrapper.h"

// Class Definition
class ZYNQMemTestWrapper: public MemTestWrapper
{

    public:

        ZYNQMemTestWrapper();
        virtual ~ZYNQMemTestWrapper() {}

        void localInit(uint32_t bank);

    private:

        // -- Implementation Specific Methods --

        void writeMemTestWrapper(uint32_t reg, uint32_t data);
        uint32_t readMemTestWrapper(uint32_t reg);
        void sleepMemTestWrapper(uint64_t ns);
        void lockMemTestWrapper(bool lock);

        bool m_localInitDone;
        uint32_t m_memBank;
};

#endif //ZYNQ_MEM_TEST_WRAPPER_H

