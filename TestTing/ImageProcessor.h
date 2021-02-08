#pragma once

struct Image {
	int x;
	int y;
	int numbChannels;
	uint8_t* imgData;
	uint8_t* imgAlpha;
};

Image removeGreenScreen(const char* path);