#ifndef ZYNQ_UPDOWN_SCALE_WPORT_H
#define ZYNQ_UPDOWN_SCALE_WPORT_H

#include <stdint.h>

#include "updown_scale_wport.h"

class ZYNQUpDownScaleWport : public UpDownScaleWport {

    public:

        ZYNQUpDownScaleWport();
        ~ZYNQUpDownScaleWport() {}
        void localInit(uint32_t path, uint32_t tile);

    private:

        // -- Implementation Specific Methods --
        void writeUpDownScaleWport(uint32_t reg, uint32_t data);
        uint32_t readUpDownScaleWport(uint32_t reg);
        void sleepUpDownScaleWport(uint64_t ns);
        void lockUpDownScaleWport(bool lock);
        bool m_localInitDone;
        uint32_t m_scalerPath;
        uint32_t m_scalerTile;
};

#endif //ZYNQ_UPDOWN_SCALE_WPORT_H
