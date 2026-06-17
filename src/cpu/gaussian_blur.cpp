#include "../../include/cpu/gaussian_blur.h"
#include <cmath>
#include <vector>

float calculateGaussian2D(float kx, float ky, float sigma)
{
    if(sigma == 0.0f) {
        return 0.0f;
    }
    float numerator = -((kx * kx) + (ky * ky));
    float denominator = 2.0f * sigma * sigma;

   return std::exp(numerator / denominator);
}

void GaussianBlur::process(Image& img) {
    
    // Step 1 — Build kernel weights
    std::vector<float> kernel(kernelSize * kernelSize);
    float sum = 0.0f;
    int half = kernelSize / 2;
    
    for(int ky = -half; ky <= half; ky++) {
        for(int kx = -half; kx <= half; kx++) {
            float weight = calculateGaussian2D(kx, ky, sigma);
            kernel[(ky + half) * kernelSize + (kx + half)] = weight;
            sum += weight;
        }
    }
    
    // Step 2 — Normalize kernel so weights sum to 1
    for(auto& w : kernel) w /= sum;
    
    // Step 3 — Apply kernel to every pixel
    std::vector<uint16_t> output(img.width * img.height);
    
    for(int y = 0; y < img.height; y++) {
        for(int x = 0; x < img.width; x++) {
            float weightedSum = 0.0f;
            
            for(int ky = -half; ky <= half; ky++) {
                for(int kx = -half; kx <= half; kx++) {
                    int clampedX = std::max(0, std::min(x + kx, img.width - 1));
                    int clampedY = std::max(0, std::min(y + ky, img.height - 1));
                    uint16_t pixelValue = img.pixels[clampedY * img.width + clampedX];
                    float kernelWeight = kernel[(ky + half) * kernelSize + (kx + half)];
                    weightedSum += pixelValue * kernelWeight;
                }
            }
            
            output[y * img.width + x] = static_cast<uint16_t>(weightedSum); 
        }
    }
    
    // Step 4 — Copy output back to image
    img.pixels = output;
}
