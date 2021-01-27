#include "ImagePanel.h"
#include <io.h>
#include <wx/log.h> 

wxBEGIN_EVENT_TABLE(ImagePanel, wxPanel)
	EVT_PAINT(ImagePanel::paintEvent)
	EVT_SIZE(ImagePanel::onSize)
	EVT_MOUSEWHEEL(ImagePanel::onScroll)
	EVT_MOTION(ImagePanel::panHandler)
	EVT_LEFT_DOWN(ImagePanel::leftDown)
	EVT_LEFT_UP(ImagePanel::leftUp)
wxEND_EVENT_TABLE()

ImagePanel::ImagePanel(wxWindow* parent, wxString file, wxBitmapType format) :
	wxPanel(parent) {
	SetDoubleBuffered(true);
	image.LoadFile(file, format);
	rendImage = image;
	isPanning = false; 
	imageOffsetX, imageOffsetY = 0;
	canvw, canvh, scale = 1;
	imgw = image.GetWidth();
	imgh = image.GetHeight();
	rendImage = image.Scale(imgw, imgh, wxIMAGE_QUALITY_NORMAL);
	aspRatio = imgw / imgh;
	ratioFit = false;
}

void ImagePanel::paintEvent(wxPaintEvent& evt) {
	wxPaintDC dc(this);
	dc.GetSize(&canvw, &canvh);
	if (!ratioFit) {
		fitToRatio(image, canvw, canvh);
		rendImage = image.Scale(imgw, imgh, wxIMAGE_QUALITY_NORMAL);
		ratioFit = true;
	}
	/*if (abs((rendImage.GetWidth() - imgw)) > 1 || abs((rendImage.GetHeight() - imgh)) > 1) {
		rendImage = image.Scale(imgw, imgh, wxIMAGE_QUALITY_NORMAL);
	}*/
	render(dc);
}

void ImagePanel::paintNow() {
	wxClientDC dc(this);
	render(dc);
}

/*Renders the image stored in rendImage*/
void ImagePanel::render(wxDC& dc) {
	dc.SetUserScale(scale, scale);
	dc.DrawBitmap(wxBitmap(rendImage),
		(canvw/scale - imgw)/2 + (panAmountX + imageOffsetX)/scale, 
		(canvh/scale - imgh)/2 + (panAmountY + imageOffsetY)/scale, false);
}

void ImagePanel::fitToRatio(wxImage image, int contw, int conth) {
	imgw = image.GetWidth();
	imgh = image.GetHeight();
	float newAspRatio = (float)contw / conth;
	if (imgh > conth) {
		imgh = contw / aspRatio;
		imgw = contw;
	}
	/*else if (oldw > contw) {
		oldh = conth;
		oldw = conth * aspRatio;
		return wxBitmap(image.Scale(oldw, oldh), wxIMAGE_QUALITY_HIGH);
	}*/
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