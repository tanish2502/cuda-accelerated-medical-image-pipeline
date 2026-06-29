#include "../../include/image_loader.h"
#include "../../include/gpu_naive/threshold.h"
#include "../../include/gpu_naive/sobel_edge.h"
#include "../../include/timer.h"
#include <iostream>

int main() {

    //load the test image
    Image originalImg = loadImage("../../data/input/test_image.tif");
    if (originalImg.pixels.empty()) {
        std::cerr << "Failed to load test image." << std::endl;
        return -1;
    }

    std::cout << "Image loaded: " << "from '../../data/input/test_image.tif'" << " of Size: " 
              << originalImg.width << "x" << originalImg.height 
              << std::endl;

    //create pipeline stages
    ThresholdGpu threshold(32000);
    Image imgForThreshold = originalImg;  // Create a copy of the original image for processing
    SobelEdgeGpu sobel;
    Image imgForSobel = originalImg;  // Create a copy of the original image for processing

    //run each stage with cpu timer
    CpuTimer timer;

    timer.start();
    threshold.process(imgForThreshold);
    timer.stop();
    std::cout << "threshold: " << timer.milliseconds() << " ms\n";

    timer.start();
    sobel.process(imgForSobel);
    timer.stop();
    std::cout << "Sobel Edge: " << timer.milliseconds() << " ms\n";

    //saveImage(img, "../../data/output/threshold_gpu.tif");
    //std::cout << "Image saved: " << "to '../../data/output/threshold_gpu.tif'" << std::endl;

    return 0;
}