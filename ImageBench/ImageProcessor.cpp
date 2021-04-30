#define STB_IMAGE_IMPLEMENTATION
#include "ImageProcessor.h"
#include "stb_image.h"
#include <iostream>
#include <memory>


ImageProcessor::ImageProcessor(wxBitmap bmp) : imageWidth(0), imageHeight(0), dataLength(0), numbChannels(0), 
											   imgData(nullptr), pixelData(bmp), prevRealtime(false), renderPanel(nullptr){
	previewRate = 5;
	imageHeight = bmp.GetHeight();
	imageWidth = bmp.GetWidth();
	iterator = wxAlphaPixelData::Iterator(pixelData);
}

//Load the Bmp to process
void ImageProcessor::loadImageDataBMP(wxBitmap bmp) {
	imageHeight = bmp.GetHeight();
	imageWidth = bmp.GetWidth();
	pixelData = wxAlphaPixelData(bmp);
	iterator = wxAlphaPixelData::Iterator(pixelData);
}

ImageProcessor::Pixel ImageProcessor::getPixel(int x, int y) {
	if (pixelData != NULL && x <= imageWidth && x >= 0 && y <= imageHeight && y >= 0) {
		int pixelStart = numbChannels * (x*y-1);
		iterator.Offset(pixelData, x, y);
		return Pixel(iterator.Red(), iterator.Green(), iterator.Blue(), iterator.Alpha());
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

void ImageProcessor::RemoveGreenScreen() {
	for (int y = 0; y < imageHeight; y++) {
		iterator.MoveTo(pixelData, 0, y);
		for (int x = 0; x < imageWidth; x++) {
			if (iterator.Green() / (iterator.Red() + iterator.Blue() + 1) > 0) {
				iterator.Alpha() = 0;
			}
			iterator++;
		}
		if (prevRealtime) {
			PreviewProcess(y);
		}
	}
}

void ImageProcessor::InvertImage() {
	for (int y = 0; y < imageHeight; y++) {
		iterator.MoveTo(pixelData, 0, y);
		for (int x = 0; x < imageWidth; x++) {
			iterator.Red() = 255 - iterator.Red();
			iterator.Green() = 255 - iterator.Green();
			iterator.Blue() = 255 - iterator.Blue();
			iterator++;
		}
		if (prevRealtime) {
			PreviewProcess(y);
		}
	}
}

void ImageProcessor::BindPanel(wxPanel* panel) {
	if (panel != nullptr) {
		renderPanel = panel;
	}
}

void ImageProcessor::PreviewProcess(int iterator) {
	if (iterator % previewRate == 0) {
		renderPanel->Refresh();
		renderPanel->Update();
	}
}

ImageProcessor::~ImageProcessor() {
	delete[] imgData;
}