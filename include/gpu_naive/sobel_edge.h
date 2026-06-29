#pragma once
#include "../pipeline_stage.h"

class SobelEdgeGpu : public PipelineStage {
public:
    SobelEdgeGpu(){}
    void process(Image& img) override;
};