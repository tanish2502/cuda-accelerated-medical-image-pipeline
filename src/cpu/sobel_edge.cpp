#include "../../include/cpu/sobel_edge.h"
#include <cmath>
#include <vector>

void SobelEdge::process(Image& img)
{
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

    std::vector<uint16_t> output(img.width * img.height);

    for(int y = 0; y < img.height; y++) {
        for(int x = 0; x < img.width; x++) {

            float sumX = 0.0f;
            float sumY = 0.0f;

            for(int ky = -1; ky <= 1; ky++) {
                for(int kx = -1; kx <= 1; kx++) {
                    // ??? clamp coordinates
                    int clampedX = std::max(0, std::min(x + kx, img.width - 1));
                    int clampedY = std::max(0, std::min(y + ky, img.height - 1));
                    uint16_t pixelValue = img.pixels[clampedY * img.width + clampedX];
                    // ??? accumulate sumX using Gx
                    sumX += pixelValue * Gx[ky+1][kx+1];
                    // ??? accumulate sumY using Gy
                    sumY += pixelValue * Gy[ky+1][kx+1];
                }
            }

            // ??? compute magnitude
            float magnitude = std::sqrt((sumX * sumX) + (sumY * sumY));
            // ??? clamp to uint16_t max and store
            output[y * img.width + x] = static_cast<uint16_t>(std::min(magnitude, 65535.0f));
            
        }
    }

    img.pixels = output;
}
