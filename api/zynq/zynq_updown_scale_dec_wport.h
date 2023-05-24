#ifndef ZYNQ_UPDOWN_SCALE_DEC_WPORT_H
#define ZYNQ_UPDOWN_SCALE_DEC_WPORT_H

#include <stdint.h>

#include "updown_scale_dec_wport.h"

class ZYNQUpDownScaleDecWport : public UpDownScaleDecWport {

    public:

        ZYNQUpDownScaleDecWport();
        ~ZYNQUpDownScaleDecWport() {}
        void localInit(uint32_t path, uint32_t tile);

    private:

        // -- Implementation Specific Methods --
        void writeUpDownScaleDecWport(uint32_t reg, uint32_t data);
        uint32_t readUpDownScaleDecWport(uint32_t reg);
        void sleepUpDownScaleDecWport(uint64_t ns);
        void lockUpDownScaleDecWport(bool lock);
        bool m_localInitDone;
        uint32_t m_scalerPath;
        uint32_t m_scalerTile;
};

#endif //ZYNQ_UPDOWN_SCALE_DEC_WPORT_H
