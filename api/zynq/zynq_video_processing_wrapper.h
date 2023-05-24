#ifndef ZYNQ_VIDEO_PROCESSING_WRAPPER_H
#define ZYNQ_VIDEO_PROCESSING_WRAPPER_H

#include <stdint.h>

#include "video_processing_wrapper.h"

class ZYNQVideoProcessingWrapper: public VideoProcessingWrapper
{

    public:

        ZYNQVideoProcessingWrapper();
        virtual ~ZYNQVideoProcessingWrapper() {}

        void init(RasterGenProg* vidmix_raster);
        bool getInitDone();

    private:

        // -- Implementation Specific Methods --

        void writeVideoProcessingWrapper(uint32_t reg, uint32_t data);
        uint32_t readVideoProcessingWrapper(uint32_t reg);

        // -- Internal Data Members --

        bool m_localInitDone;
};

#endif //ZYNQ_VIDEO_PROCESSING_WRAPPER_H
