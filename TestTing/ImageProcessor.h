#pragma once

class ImageProcessor {
public:
	int imageWidth, imageHeight, numbChannels;
	uint8_t* imgData;
	uint8_t* imgAlpha;
	uint8_t* fullImageData; 

	void loadImage(const char* path);
};