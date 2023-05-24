#ifndef ZYNQ_PLAYOUT_CTRL_H
#define ZYNQ_PLAYOUT_CTRL_H

#include <stdint.h>
#include "playout_ctrl.h"

class ZYNQPlayoutCtrl : public PlayoutCtrl {

    public:

        ZYNQPlayoutCtrl();
        ~ZYNQPlayoutCtrl() {}

        // -- Basic Control Functions

        // Init
        void localInit(uint32_t path);

    private:

        // -- Implementation Specific Methods --
        void writePlayoutCtrl(uint32_t reg, uint32_t data);
        uint32_t readPlayoutCtrl(uint32_t reg);
        void sleepPlayoutCtrl(uint64_t ns);
        void lockPlayoutCtrl(bool lock);

        // -- Private Data Members --
        bool m_localInitDone;
        uint32_t m_scalerPath;
};

#endif //ZYNQ_PLAYOUT_CTRL_H
