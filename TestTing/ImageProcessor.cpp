#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include "ImageProcessor.h"
#include <memory> 

ImageProcessor::ImageProcessor() : imageWidth(0), imageHeight(0), numbChannels(0), imgData(nullptr) {

}

//Load image to process
void ImageProcessor::loadImageDataRGBA(const char* path) {
	int channelsRequired = 4;
	int x, y;
	imgData = stbi_load(path, &x, &y, &numbChannels, channelsRequired);

	if (imgData != NULL) {
		imageWidth = x;
		imageHeight = y;
	}
}

ImageProcessor::Pixel ImageProcessor::getPixel(int x, int y) {
	if (imgData != NULL && x <= imageWidth && x >= 0 && y <= imageHeight && y >= 0) {
		int pixelStart = 4 * (x*y-1);
		return Pixel(imgData[pixelStart], imgData[pixelStart + 1], imgData[pixelStart + 2], imgData[pixelStart + 3]);
	}
	else {
		return Pixel(-101,-101,-101,-101);
	}
}

ImageProcessor::~ImageProcessor() {
	delete[] imgData;
}