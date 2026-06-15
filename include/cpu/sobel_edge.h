#pragma once
#include "../pipeline_stage.h"

class SobelEdge : public PipelineStage {
public:
    SobelEdge(){}

    void process(Image& img) override;
};
