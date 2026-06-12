#pragma once
#include "./image_types.h"

class PipelineStage{
public:
    virtual ~PipelineStage(){}

    virtual void process(Image& img) = 0;   //in place processing being used here. Modify in place image after processing.
};

