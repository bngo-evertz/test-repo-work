#ifndef ZYNQ_UPDOWN_SCALE_WRAPPER_H
#define ZYNQ_UPDOWN_SCALE_WRAPPER_H

#include <stdint.h>

#include "updown_scale_wrapper.h"

class ZYNQUpDownScaleWrapper: public UpDownScaleWrapper
{

    public:

        ZYNQUpDownScaleWrapper();
        virtual ~ZYNQUpDownScaleWrapper() {}

        void localInit(uint32_t path);

    private:

        // -- Implementation Specific Methods --

        void writeUpDownScaleWrapper(uint32_t reg, uint32_t data);
        uint32_t readUpDownScaleWrapper(uint32_t reg);
        void sleepUpDownScaleWrapper(uint64_t ns);
        void lockUpDownScaleWrapper(bool lock);

        // -- Internal Data Members --

        bool m_localInitDone;
        uint32_t m_scalerPath;
};

#endif //ZYNQ_UPDOWN_SCALE_WRAPPER_H
