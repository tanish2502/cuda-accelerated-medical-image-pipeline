#pragma once
#include "./image_types.h"
#include <cstring>

Image loadImage(const std::string& imageFilePath);

void saveImage(const Image& img, const std::string& imageFilePath);
