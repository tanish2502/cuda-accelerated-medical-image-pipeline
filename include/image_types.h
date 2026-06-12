#pragma once
#include <vector>
#include <string>

struct Image {

	// Dimensions
	int width;
	int height;

	//host side - Pixel Data
	std::vector<uint16_t> pixels;

	//Device Pointer - GPU Side
	uint16_t* d_pixels = nullptr;

	//Intensity MetaData
	uint16_t minVal = 0;
	uint16_t maxVal = 65535;

	//Utility - total pixel count
	int size() const {
		return width * height;
	}

	//Utility - bytes for CUDA memory
	size_t byteSize() const {
		return width * height * sizeof(uint16_t);
	}


};
