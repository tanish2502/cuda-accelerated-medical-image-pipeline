#pragma once
#include "../pipeline_stage.h"

class ThresholdGpu : public PipelineStage{
public:
    ThresholdGpu(uint16_t thresholdValue) : thresholdValue(thresholdValue) {}
    void process(Image& img) override;
private:
    uint16_t thresholdValue;
};
