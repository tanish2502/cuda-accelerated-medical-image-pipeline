#include "../../include/image_loader.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

Image loadImage(const std::string& imageFilePath) {
    cv::Mat mat = cv::imread(imageFilePath, cv::IMREAD_UNCHANGED | cv::IMREAD_GRAYSCALE); // Load as grayscale, keep original 16-bit depth
    if (mat.empty()) {
        std::cerr << "Error: Could not load image: " << imageFilePath << std::endl;
        return Image();
    }

    if(mat.type() != CV_16UC1) {
        mat.convertTo(mat, CV_16UC1, 257.0);
    }

    Image img;
    img.width = mat.cols;
    img.height = mat.rows;
    img.pixels.resize(img.width * img.height);

    for(int y = 0; y < img.height; y++) {
        for(int x = 0; x < img.width; x++) {
            img.pixels[y * img.width + x] = mat.at<uint16_t>(y, x);
        }
    }
    return img;
}

void saveImage(const Image& img, const std::string& imageFilePath){

    //create OpenCV Mat from Image struct
    //CV_16UC1 means 16-bit unsigned single channel (grayscale) image
    cv::Mat mat(img.height, img.width, CV_16UC1);

    // Copy pixel data from Image struct to OpenCV Mat
    for(int y = 0; y < img.height; y++) {
        for(int x = 0; x < img.width; x++) {
            mat.at<uint16_t>(y, x) = img.pixels[y * img.width + x];
        }
    }

    if(cv::imwrite(imageFilePath, mat)) {   //imwrite automatically detects the format based on the file extension
        std::cout << "Image saved: " << imageFilePath << std::endl;
    }
    else {
        std::cerr << "Error: Could not save image: " << imageFilePath << std::endl;
    }
}
