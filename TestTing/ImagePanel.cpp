#include "ImagePanel.h"
#include "wx/timer.h"
#include <wx/rawbmp.h>

//TODO CONST
wxBEGIN_EVENT_TABLE(ImagePanel, wxPanel)
EVT_PAINT(ImagePanel::paintEvent)
EVT_SIZE(ImagePanel::onSize)
EVT_MOUSEWHEEL(ImagePanel::onScroll)
EVT_MOTION(ImagePanel::panHandler)
EVT_LEFT_DOWN(ImagePanel::leftDown)
EVT_LEFT_UP(ImagePanel::leftUp)
//EVT_RIGHT_DOWN(ImagePanel::drawAtMouse)
wxEND_EVENT_TABLE()

ImagePanel::ImagePanel(wxWindow* parent) :
	wxPanel(parent), isPanning(false), isLoading(false), aspRatio(0), imageOffsetX(0), imageOffsetY(0), 
	canvw(0), canvh(0), scale(1), imagePosX(0), imagePosY(0), imgh(0), imgw(0), mouseX(0), mouseY(0), panAmountX(0), panAmountY(0)
{
	loadingScreen.LoadFile("loadingScreen.png");
	SetDoubleBuffered(true);
}

//Load image using its path. 
void ImagePanel::loadImage(wxString path) {
	isLoading = true;
	Refresh();
	Update();
	wxImage image;
	image.LoadFile(path, wxBITMAP_TYPE_PNG);
	if (image.IsOk()) {
		initImageProps();
		rendImage = (wxBitmap)image;
		Refresh();
	}
}

//Load RGB/RGBA image using raw data. Converts to bitmap before render.  
void ImagePanel::loadImage(uint8_t* imageData, int x, int y, int channels) {
	isLoading = true;
	Refresh();
	Update();
	//Convert the raw data to bitmap first.
	wxBitmap bitmapImage = RGBAtoBitmap(imageData, x, y);
	if (bitmapImage.IsOk()) {
		rendImage = bitmapImage;
		resetTransforms();
		initBitmapProps(bitmapImage);
		scaleToRatio(canvw, canvh);
		Refresh();
	}
}

//Load RGB image using raw data. Converts to wxImage then to bitmap. 
void ImagePanel::loadImage(uint8_t* imageData, int x, int y){
	isLoading = true;
	Refresh();
	Update();
	wxImage image = wxImage(x, y, imageData, true);
	if (image.IsOk()) {
		rendImage = (wxBitmap)image;
		resetTransforms();
		initImageProps();
		scaleToRatio(canvw, canvh);
		Refresh();
	}
}

//Load RGBA image using raw data. Converts to wxImage then to bitmap. 
void ImagePanel::loadImage(uint8_t* imageData, uint8_t* imageAlpha, int x, int y){
	isLoading = true;
	Refresh();
	Update();
	wxImage image = wxImage(x, y, imageData, imageAlpha, true);
	if (image.IsOk()) {
		rendImage = (wxBitmap)image;
		resetTransforms();
		initImageProps();
		scaleToRatio(canvw, canvh);
		Refresh();
	}
}

//Converts raw RGB/RGBA data to a bitmap. 
wxBitmap ImagePanel::RGBAtoBitmap(uint8_t* rgba, int w, int h)
{
	wxBitmap bitmap = wxBitmap(w, h, 32);
	if (!bitmap.Ok()) {
		//delete bitmap;
		return NULL;
	}

	wxAlphaPixelData bmdata(bitmap);
	if (bmdata == NULL) {
		wxLogDebug(wxT("getBitmap() failed"));
		//delete bitmap;
		return NULL;
	}

	wxAlphaPixelData::Iterator dst(bmdata);

	for (int y = 0; y < h; y++) {
		dst.MoveTo(bmdata, 0, y);
		for (int x = 0; x < w; x++) {
			// wxBitmap contains rgb values pre-multiplied with alpha
			unsigned char a = rgba[3];
			dst.Red() = rgba[0] * a / 255;
			dst.Green() = rgba[1] * a / 255;
			dst.Blue() = rgba[2] * a / 255;
			dst.Alpha() = a;
			dst++;
			rgba += 4;
		}
	}
	return bitmap;
}

void ImagePanel::setLoading(bool isLoading){
	ImagePanel::isLoading = isLoading;
}

void ImagePanel::initImageProps(){
	imgw = rendImage.GetWidth();
	imgh = rendImage.GetHeight();
	aspRatio = imgw / imgh;
}

void ImagePanel::initBitmapProps(wxBitmap bitmap) {
	imgw = bitmap.GetWidth();
	imgh = bitmap.GetHeight();
	aspRatio = imgw / imgh;
}

void ImagePanel::resetTransforms() {
	scale = 1;
	imageOffsetX = 0;
	imageOffsetY = 0;
}

void ImagePanel::scaleToRatio(int contw, int conth) {
	/*if (image.IsOk()) {
		float newAspRatio = (float)contw / conth;
		if (imgh < imgw) {
			imgh = contw / aspRatio;
			imgw = contw;
		}
		else {
			imgh = conth;
			imgw = conth * aspRatio;
		}
	}*/
	float newAspRatio = (float)contw / conth;
	float newImgw, newImgh;
	if (imgh < imgw && imgh > conth) {
		newImgh = contw / aspRatio;
		newImgw = contw;
		scale = newImgh / imgh;
	}
	else {
		newImgh = conth;
		newImgw = conth * aspRatio;
		scale = newImgh / imgh;
	}
}

//Does not render, but prepares to render. 
void ImagePanel::paintEvent(wxPaintEvent& evt) {
	wxPaintDC dc(this);
	dc.GetSize(&canvw, &canvh);
	//Calculates the images offset based on scale, centers it. 
	imagePosX = (canvw / scale - imgw) / 2 + (panAmountX + imageOffsetX) / scale;
	imagePosY = (canvh / scale - imgh) / 2 + (panAmountY + imageOffsetY) / scale;

	if (rendImage.IsOk()) {
		render(dc);
	}
	if (isLoading) {
		dc.Clear();
		renderLoading(dc);
		isLoading = false;
	}
}
 
void ImagePanel::paintNow() {
	wxClientDC dc(this);
	render(dc);
}

//The render function which does the actual rendering to the screen. 
void ImagePanel::render(wxDC& dc) {
	dc.SetUserScale(scale, scale);
	dc.DrawBitmap(rendImage, imagePosX, imagePosY, false);
}

void ImagePanel::renderLoading(wxDC& dc) {
	    dc.SetUserScale(1, 1);
		dc.DrawBitmap((wxBitmap)loadingScreen, (canvw - loadingScreen.GetWidth()) /2, (canvh -loadingScreen.GetHeight()) /2);
}

//Event Handlers
void ImagePanel::onScroll(wxMouseEvent& evt){
	if (evt.GetWheelRotation() > 0) {
		if(scale < 10)
		   scale+=0.07f * scale;
	}
	else if(scale >= 0.1){
		scale-=0.07f * scale;
	}
	Refresh();
	evt.Skip();
}

void ImagePanel::panHandler(wxMouseEvent& evt) {
	if (isPanning) {
		float newMouseX = evt.GetX();
		float newMouseY = evt.GetY();
		panAmountX = newMouseX - mouseX;
		panAmountY = newMouseY - mouseY;
		Refresh();
		evt.Skip();
	}
	evt.Skip();
}

void ImagePanel::leftDown(wxMouseEvent& evt) {
	isPanning = true; 
	mouseX = evt.GetX();
	mouseY = evt.GetY();
}

void ImagePanel::leftUp(wxMouseEvent& evt) {
	isPanning = false;
	imageOffsetX += panAmountX;
	imageOffsetY += panAmountY;
	panAmountX = 0;
	panAmountY = 0;
	Refresh();
}

void ImagePanel::rightDown(wxMouseEvent& evt) {
	wxPoint pixelLoc = evt.GetPosition();
	std::cout << pixelLoc.x << "\n" << pixelLoc.y << "\n";
}

//void ImagePanel::drawAtMouse(wxMouseEvent& evt) {
//	wxPoint pixelLoc = evt.GetPosition();;
//	double x = (double)(pixelLoc.x) / (canvw);
//	double y = (double)(pixelLoc.y) / (canvh);
//	double newyVal = (pixelLoc.y - imagePosY) * scale;
//	std::cout << "\n\nMouse Location:  X: " << pixelLoc.x << " Y: " << pixelLoc.y;
//	std::cout << "\nNormalized Values: " << " X Value: " << x << " Y Value: " << y;
//	std::cout << "\nImage Positions: imagePosX: " << imagePosX * scale << " imagePosY: " << imagePosY * scale;
//	std::cout << "\nCalculated Pixel Coordinate: X: " << imgw / 2 << "  Y: " << newyVal;
//	if (pixelLoc.y >= imagePosY) {
//		rendImage.SetRGB(50, newyVal, 0, 255, 0);
//	}
//	updateImage();
//	Refresh();
//}

void ImagePanel::onSize(wxSizeEvent& evt) {
	Refresh();
	evt.Skip();
}

void ImagePanel::bgErase(wxEraseEvent& evt) {

}

