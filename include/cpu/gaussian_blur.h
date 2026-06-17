#pragma once
#include "../pipeline_stage.h"

class GaussianBlur : public PipelineStage{

public:
    GaussianBlur(float sigma, int kernelSize) : sigma(sigma), kernelSize(kernelSize){}

    void process(Image& img) override;

private:
    float sigma;
    int kernelSize;    
};
