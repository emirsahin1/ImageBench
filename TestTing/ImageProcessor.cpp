#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include "ImageProcessor.h"

//Load image to process
void ImageProcessor::loadImage(const char* path) {
	int channelsRequired = 4;
	int x, y;
	
	fullImageData = stbi_load(path, &x, &y, &numbChannels, channelsRequired);
	imgData = stbi_load(path, &x, &y, &numbChannels, 3);
	imgAlpha = NULL;

	if (numbChannels > 3) {
		imgAlpha = new uint8_t[x * y];
		for (int i = 3, j = 0; i < x * y * numbChannels; i += 4, j++) {
			imgAlpha[j] = fullImageData[i];
		}
	}
	if (fullImageData != NULL) {
		imageWidth = x;
		imageHeight = y;
		imgData;
		imgAlpha;
	}
}