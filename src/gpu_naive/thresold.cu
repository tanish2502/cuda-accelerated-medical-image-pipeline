#include "../../include/gpu_naive/threshold.h"

__global__ void thresholdKernel(const uint16_t* input, uint16_t* output, int width, int height, uint16_t thresholdValue) {
    
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if(x >= width || y >= height) return;

    uint16_t pixelValue = input[y * width + x];
    uint16_t result = (pixelValue >= thresholdValue) ? 65535 : 0;
    output[y * width + x] = result; 
}

void ThresholdGpu::process(Image& img) {

        
}
