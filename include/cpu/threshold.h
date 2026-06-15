#pragma once
#include "../pipeline_stage.h"

class Threshold : public PipelineStage{
public:
    Threshold(uint16_t thresholdValue) : thresholdValue(thresholdValue) {}
    void process(Image& img) override;
private:
    uint16_t thresholdValue;
};
