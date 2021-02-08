#include "ImagePanel.h"
#include <io.h>
#include <wx/log.h>
#include <iostream>

wxBEGIN_EVENT_TABLE(ImagePanel, wxPanel)
	EVT_PAINT(ImagePanel::paintEvent)
	EVT_SIZE(ImagePanel::onSize)
	EVT_MOUSEWHEEL(ImagePanel::onScroll)
	EVT_MOTION(ImagePanel::panHandler)
	EVT_LEFT_DOWN(ImagePanel::leftDown)
	EVT_LEFT_UP(ImagePanel::leftUp)
wxEND_EVENT_TABLE()

ImagePanel::ImagePanel(wxWindow* parent) :
	wxPanel(parent) {
	SetDoubleBuffered(true);
	isPanning = false; 
	imageOffsetX, imageOffsetY = 0;
	canvw, canvh, scale = 1;
}

void ImagePanel::loadImage(wxString path) {
	image.LoadFile(path, wxBITMAP_TYPE_ANY);
	if (image.IsOk()) {
		initImageProps();
		Refresh();
	}
}

void ImagePanel::loadImage(uint8_t* imageData, int x, int y)
{
	image = wxImage(x, y, imageData, true);
	if (image.IsOk()) {
		initImageProps();
		Refresh();
	}
}

void ImagePanel::loadImage(uint8_t* imageData, uint8_t* imageAlpha, int x, int y)
{
	image = wxImage(x, y, imageData, imageAlpha, true);
	if (image.IsOk()) {
		initImageProps();
		Refresh();
	}
}

void ImagePanel::initImageProps()
{
	scale = 1;
	imageOffsetX = 0;
	imageOffsetY = 0;
	imgw = image.GetWidth();
	imgh = image.GetHeight();
	aspRatio = imgw / imgh;
	//Fits the image w and h to the desired ratio before render. 
	fitImageToRatio(canvw, canvh);
	rendImage = (wxBitmap)image.Scale(imgw, imgh, wxIMAGE_QUALITY_BILINEAR);
}

void ImagePanel::paintEvent(wxPaintEvent& evt) {
	wxPaintDC dc(this);
	dc.GetSize(&canvw, &canvh);
	if (image.IsOk()) {
		/*if (abs((rendImage.GetWidth() - imgw)) > 1 || abs((rendImage.GetHeight() - imgh)) > 1) {
			rendImage = image.Scale(imgw, imgh, wxIMAGE_QUALITY_NORMAL);
		}*/
		render(dc);
	}
}

void ImagePanel::paintNow() {
	wxClientDC dc(this);
	render(dc);
}

void ImagePanel::render(wxDC& dc) {
	dc.SetUserScale(scale, scale);
	dc.DrawBitmap(rendImage,
		(canvw/scale - imgw)/2 + (panAmountX + imageOffsetX)/scale, 
		(canvh/scale - imgh)/2 + (panAmountY + imageOffsetY)/scale, false);
}

void ImagePanel::fitImageToRatio(int contw, int conth) {
	if (image.IsOk()) {
		float newAspRatio = (float)contw / conth;
		//if (imgh > conth) {
			imgh = contw / aspRatio;
			imgw = contw;
		//}
	    /*else if (imgw > contw) {
			imgh = conth;
			imgw = conth * aspRatio;
		}*/
	}
	//else return image;
}
	
void ImagePanel::onScroll(wxMouseEvent& evt){
	if (evt.GetWheelRotation() > 0) {
		if(scale < 25)
		   scale+=0.3f;
	}
	else if(scale >= 0.3){
		scale-=0.3f;
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

void ImagePanel::onSize(wxSizeEvent& evt) {
	Refresh();
	evt.Skip();
}

void ImagePanel::bgErase(wxEraseEvent& evt) {

}