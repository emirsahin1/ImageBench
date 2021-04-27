#pragma once
#include <wx/wx.h>
#include <wx/rawbmp.h>

class ImageProcessor {

private:
	wxAlphaPixelData pixelData;
	wxAlphaPixelData::Iterator iterator;

public:
	struct Pixel {
		int r, g, b, a;
		Pixel(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {
		};
	};
	friend std::ostream& operator<<(std::ostream& stream, const ImageProcessor::Pixel& pixel) {
		stream << "R: " << pixel.r << " G: " << pixel.g << " B: " << pixel.b << " A: "<< pixel.a << std::endl;
		return stream;
	}

	bool prevRealtime;
	int imageWidth, imageHeight, dataLength, numbChannels, previewRate;
	wxPanel* renderPanel;
	uint8_t* imgData;

	ImageProcessor::Pixel getPixel(int x, int y);
	void RemoveGreenScreen();
	void InvertImage();
	void BindPanel(wxPanel* panel);
	void loadImageDataBMP(wxBitmap bmp);
	void boxBlur();
	void loadImageDataRGBA(const char* path);

	ImageProcessor(wxBitmap bmp);
	~ImageProcessor();

};