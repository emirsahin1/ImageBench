#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include "ImageProcessor.h"


Image removeGreenScreen(const char* path) {
	int channelsRequired = 4;
	int x, y, numbChannels;
	
	Image img;
	uint8_t* fullImageData = stbi_load(path, &x, &y, &numbChannels, channelsRequired);
	uint8_t* imageDataUse = stbi_load(path, &x, &y, &numbChannels, 3);
	uint8_t* imageAlpha = NULL;

	if (numbChannels > 3) {
		imageAlpha = new uint8_t[x * y];
		for (int i = 3, j = 0; i < x * y * numbChannels; i += 4, j++) {
			imageAlpha[j] = fullImageData[i];
		}
	}
	if (fullImageData != NULL) {
		img.x = x;
		img.y = y;
		img.imgData = imageDataUse;
		img.imgAlpha = imageAlpha;
	}

	return img;
}