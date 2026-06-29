#include "../../include/gpu_naive/threshold.h"
#include "../../src/common/timer.cu"
#include <cuda_runtime.h>
#include <iostream>

_global_ void thresholdKernel(const uint16_t* input, uint16_t* output, int width, int height, uint16_t thresholdValue) {

    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if(x >= width || y >= height) return;

    uint16_t pixelValue = input[y * width + x];  //raw major access
    uint16_t result = (pixelValue >= thresholdValue) ? 65535 : 0;
    output[y * width + x] = result;
}

void ThresholdGpu::process(Image& img) {
    // Allocate device memory
    cudaMalloc((void**)&img.d_pixels, img.byteSize());

    // Copy host → device
    cudaMemcpy(img.d_pixels, img.pixels.data(),
               img.byteSize(), cudaMemcpyHostToDevice);

    // Launch kernel
    dim3 blockSize(16, 16);
    dim3 gridSize(
        (img.width  + 15) / 16,
        (img.height + 15) / 16
    );

    GpuTimer gpuTimer;
    gpuTimer.start();
    thresholdKernel<<<gridSize, blockSize>>>(
        img.d_pixels,
        img.d_pixels,
        img.width,
        img.height,
        thresholdValue
    );
    gpuTimer.stop();
    gpuTimer.sync();
    std::cout << "threshold (GPU): " << gpuTimer.milliseconds() << " ms\n";

    // Copy device → host
    cudaMemcpy(img.pixels.data(), img.d_pixels,
               img.byteSize(), cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(img.d_pixels);
    img.d_pixels = nullptr;
}