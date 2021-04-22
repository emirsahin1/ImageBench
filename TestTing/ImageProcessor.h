#pragma once

class ImageProcessor {

public:
	struct Pixel {
		int r, g, b, a;

		Pixel() : r(0), g(0), b(0), a(0) {
		};
		Pixel(int r, int g, int b, int a) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		};
	};

	friend std::ostream& operator<<(std::ostream& stream, const ImageProcessor::Pixel& pixel) {
		stream << "R: " << pixel.r << " G: " << pixel.g << " B: " << pixel.b << " A: "<< pixel.a << std::endl;
		return stream;
	}

	int imageWidth, imageHeight, numbChannels;
	uint8_t* imgData;
	ImageProcessor();
	~ImageProcessor();
	void loadImageDataRGBA(const char* path);
	ImageProcessor::Pixel getPixel(int x, int y);

};