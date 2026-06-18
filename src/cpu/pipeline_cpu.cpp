#include "../../include/cpu/gaussian_blur.h"
#include "../../include/cpu/sobel_edge.h"
#include "../../include/cpu/histogram_eq.h"
#include "../../include/cpu/threshold.h"
#include "../../include/timer.h"
#include <iostream>
#include <vector>

Image createTestImage(int width, int height) {
    Image img;
    img.width = width;
    img.height = height;
    img.pixels.resize(width * height);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            img.pixels[y * width + x] = 
                static_cast<uint16_t>((x + y) % 65535);
        }
    }
    return img;
}

int main() {
    // Create test image
    Image img = createTestImage(1024, 1024);
    
    std::cout << "Image created: " 
              << img.width << "x" << img.height 
              << std::endl;

    // Create pipeline stages
    GaussianBlur gaussian(1.5f, 5);
    SobelEdge sobel;
    HistogramEq histEq;
    Threshold threshold(32000);

    // Run each stage with CpuTimer
    CpuTimer timer, totalTimer;

    totalTimer.start();
    timer.start();
    gaussian.process(img);
    timer.stop(); 
    std::cout << "Gaussian Blur: " << timer.milliseconds() << " ms\n";     

    timer.start();
    sobel.process(img);
    timer.stop();
    std::cout << "Sobel Edge: " << timer.milliseconds() << " ms\n";     
    
    timer.start();
    histEq.process(img);
    timer.stop();
    std::cout << "histEq: " << timer.milliseconds() << " ms\n";     
    
    timer.start();
    threshold.process(img);
    timer.stop();
    std::cout << "threshold: " << timer.milliseconds() << " ms\n";     
    
    totalTimer.stop();
    std::cout << "Total time taken by the full pipeline: " << totalTimer.milliseconds() << " ms\n";
    return 0;
}
