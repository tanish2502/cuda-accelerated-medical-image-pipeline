#include "../../include/gpu_naive/sobel_edge.h"
#include "../../include/timer.h"
#include <cuda_runtime.h>
#include <iostream>

__global__ void sobelEdgeKernel(const uint16_t* input, uint16_t* output, int width, int height) {

    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    // Check if the pixel is within the image boundaries
    if(x >= width || y >= height) return;
    
    //fixed Sobel kernels
    const int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    const int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    float sumX = 0.0f;
    float sumY = 0.0f;

    for(int ky = -1; ky <= 1; ky++) {
        for(int kx = -1; kx <= 1; kx++) {
            //clamp coordinates
            int clampedX = max(0, min(x + kx, width - 1));
            int clampedY = max(0, min(y + ky, height - 1));
            uint16_t pixelValue = input[clampedY * width + clampedX];
            // accumulate sumX using Gx
            sumX += pixelValue * Gx[ky+1][kx+1];
            // accumulate sumY using Gy
            sumY += pixelValue * Gy[ky+1][kx+1];
        }
    }

    // compute magnitude
    float magnitude = sqrtf((sumX * sumX) + (sumY * sumY));
    // clamp to uint16_t max and store
    output[y * width + x] = static_cast<uint16_t>(min(magnitude, 65535.0f));
}

void SobelEdgeGpu::process(Image& img) {

    uint16_t* d_output = nullptr;

    // Allocate device memory
    cudaMalloc((void**)&img.d_pixels, img.byteSize());
    cudaMalloc((void**)&d_output, img.byteSize());

    // Copy host → device
    cudaMemcpy(img.d_pixels, img.pixels.data(),
               img.byteSize(), cudaMemcpyHostToDevice);

    // Define block and grid sizes
    dim3 blockSize(16, 16);
    dim3 gridSize((img.width + blockSize.x - 1) / blockSize.x,
                  (img.height + blockSize.y - 1) / blockSize.y);

    GpuTimer gpuTimer;
    gpuTimer.start();
    // Launch the kernel
    sobelEdgeKernel<<<gridSize, blockSize>>>(img.d_pixels, d_output, img.width, img.height);
    gpuTimer.stop();

    cudaDeviceSynchronize();  // Ensure kernel execution is complete before proceeding
    gpuTimer.sync();  // Ensure timer is synchronized with the device
    std::cout << "Sobel Edge GPU: " << gpuTimer.milliseconds() << " ms\n";

    // Copy device → host
    cudaMemcpy(img.pixels.data(), d_output, img.byteSize(), cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(img.d_pixels);
    cudaFree(d_output);
    img.d_pixels = nullptr;  // Reset device pointer to avoid dangling pointer
    d_output = nullptr;  // Reset device pointer to avoid dangling pointer
}