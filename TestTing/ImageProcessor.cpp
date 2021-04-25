#define STB_IMAGE_IMPLEMENTATION
#include "ImageProcessor.h"
#include "stb_image.h"
#include <iostream>
#include <memory>


ImageProcessor::ImageProcessor(wxBitmap bmp) : imageWidth(0), imageHeight(0), dataLength(0), numbChannels(0), imgData(nullptr), pixelData(bmp){
	imageHeight = bmp.GetHeight();
	imageWidth = bmp.GetWidth();
	iterator = wxAlphaPixelData::Iterator(pixelData);
}

//Load image to process
void ImageProcessor::loadImageDataRGBA(const char* path) {
	int channelsRequired = 4;
	int x, y;
	imgData = stbi_load(path, &x, &y, &numbChannels, channelsRequired);

	if (imgData != NULL) {
		imageWidth = x;
		imageHeight = y;
		dataLength = x * y * numbChannels;
	}
}

void ImageProcessor::loadImageDataBMP(wxBitmap bmp) {
	imageHeight = bmp.GetHeight();
	imageWidth = bmp.GetWidth();
	pixelData = wxAlphaPixelData(bmp);
	iterator = wxAlphaPixelData::Iterator(pixelData);
}

ImageProcessor::Pixel ImageProcessor::getPixel(int x, int y) {
	if (imgData != NULL && x <= imageWidth && x >= 0 && y <= imageHeight && y >= 0) {
		int pixelStart = numbChannels * (x*y-1);
		return Pixel(imgData[pixelStart], imgData[pixelStart + 1], imgData[pixelStart + 2], imgData[pixelStart + 3]);
	}
	else {
		return Pixel(-101,-101,-101,-101);
	}
}

void ImageProcessor::boxBlur() {
	int pixelAvg;
	for (int i = 0; i < dataLength; i += 4) {
		pixelAvg = imgData[i];
	}
}

void ImageProcessor::paintRed(wxPanel* panel) {
	/*for (int y = 0; y < imageHeight; y++) {
		iterator.MoveTo(pixelData, 0, y);
		for (int x = 0; x < imageWidth; x++) {
			iterator.Red() = 255 - iterator.Red();
			iterator.Green() = 255 - iterator.Green();
			iterator.Blue() = 255 - iterator.Blue();
			iterator++;
		}
		panel->Refresh();
		panel->Update();
	}*/
	for (int y = 0; y < imageHeight; y++) {
		iterator.MoveTo(pixelData, 0, y);
		for (int x = 0; x < imageWidth; x++) {
			iterator.Green() = (iterator.Blue() - iterator.Red()) * iterator.Green();
			iterator++;
		}
		if (y % 2 == 0) {
			panel->Refresh();
			panel->Update();
		}
	}
}

ImageProcessor::~ImageProcessor() {
	delete[] imgData;
}