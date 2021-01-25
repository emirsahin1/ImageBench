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
	isPanning = false; 
	imageOffsetX, imageOffsetY = 0;
	canvw, canvh, scale = 1;
	imgw = image.GetWidth();
	imgh = image.GetHeight();
	aspRatio = imgw / imgh;
}

void ImagePanel::paintEvent(wxPaintEvent& evt) {
	wxPaintDC dc(this);
	dc.GetSize(&canvw, &canvh);
	rendImage = fitToRatio(image, canvw, canvh);
	render(dc);
}

void ImagePanel::paintNow() {
	wxClientDC dc(this);
	render(dc);
}

/*Renders the image stored in rendImage*/
void ImagePanel::render(wxDC& dc) {
	//dc.SetUserScale(scale, scale);
	dc.DrawBitmap(rendImage,  (panAmountX + imageOffsetX)/scale, ((canvh - imgh)/2) + (panAmountY + imageOffsetY)/scale, false);
}

wxBitmap ImagePanel::fitToRatio(wxImage image, int contw, int conth) {
	imgw = image.GetWidth();
	imgh = image.GetHeight();
	float newAspRatio = (float)contw / conth;
	if (imgh > conth) {
		imgh = contw / aspRatio;
		imgw = contw;
		return wxBitmap(image.Scale(imgw, imgh), wxIMAGE_QUALITY_HIGH);
	}
	/*else if (oldw > contw) {
		oldh = conth;
		oldw = conth * aspRatio;
		return wxBitmap(image.Scale(oldw, oldh), wxIMAGE_QUALITY_HIGH);
	}*/
	else return wxBitmap(image);
}
	
void ImagePanel::onScroll(wxMouseEvent& evt){
	if (evt.GetWheelRotation() > 0) {
		if(scale < 10)
		   scale+=0.1;
	}
	else if(scale > 1){
		scale-=0.1;
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