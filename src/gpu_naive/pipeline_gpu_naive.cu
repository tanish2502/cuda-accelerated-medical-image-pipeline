#include "../include/image_loader.h"
#include "../include/gpu_naive/threshold.h"
#include "../include/timer.h"
#include <iostream>

int main() {
    // Load test image
    Image img = loadImage("../../data/input/test_image.tif");

    if(img.pixels.empty()) {
        std::cerr << "Image load failed!\n";
        return -1;
    }

    std::cout << "Image loaded: "
              << img.width << "x" << img.height << "\n";

    // Test ThresholdGpu
    ThresholdGpu threshold(32000);

    CpuTimer timer;
    timer.start();
    threshold.process(img);
    timer.stop();

    std::cout << "ThresholdGpu: "
              << timer.milliseconds() << " ms\n";

    // Save output
    saveImage(img, "../../data/output/threshold_gpu.tif");

    return 0;
}
