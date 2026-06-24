#include <opencv2/opencv.hpp>
#include "../../include/image_loader.h"
#include "../../include/image_types.h"
#include "../../include/cpu/gaussian_blur.h"
#include "../../include/cpu/sobel_edge.h"
#include "../../include/cpu/histogram_eq.h"
#include "../../include/cpu/threshold.h"
#include "../../include/timer.h"
#include <iostream>
#include <vector>
#include <cmath>

void generateTestImage(const std::string& path, 
                       int width, int height) {
    cv::Mat mat(height, width, CV_16UC1);
    
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            float dx = x - width/2.0f;
            float dy = y - height/2.0f;
            float dist = std::sqrt(dx*dx + dy*dy);
            float maxDist = std::sqrt(
                (width/2.0f)*(width/2.0f) + 
                (height/2.0f)*(height/2.0f));
            
            // Circular gradient simulating brain MRI(roughly)
            float val = 65535.0f * 
                        std::max(0.0f, 1.0f - dist/maxDist);
            
            // Add some texture variation
            val *= (0.8f + 0.2f * 
                   std::sin(x * 0.1f) * 
                   std::cos(y * 0.1f));
            
            mat.at<uint16_t>(y, x) = 
                static_cast<uint16_t>(
                    std::min(val, 65535.0f));
        }
    }
    
    cv::imwrite(path, mat);
    std::cout << "Generated " << width << "x" << height 
              << " test image at: " << path << "\n";
}

int main() {
    // Create test image
    generateTestImage("../../data/input/test_image.tif", 1024, 1024);
    
    Image img = loadImage("../../data/input/test_image.tif");
    if (img.pixels.empty()) {
        std::cerr << "Failed to load test image." << std::endl;
        return -1;
    }

    std::cout << "Image loaded: " << "from '../../data/input/test_image.tif'" << " of Size: " 
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
