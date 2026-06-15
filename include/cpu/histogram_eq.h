#pragma once
#include "../pipeline_stage.h"

class HistogramEq : public PipelineStage{
public:
    HistogramEq(){}
    void process(Image& img) override;

};
