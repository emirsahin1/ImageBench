#pragma once
#include <wx/wx.h>


class ImagePanel : public wxPanel
{
private:
	int canvw, canvh;
	float imgh, imgw, scale, aspRatio, imageOffsetX, imageOffsetY;
	float mouseX, mouseY, panAmountX, panAmountY;
	bool isPanning;
	wxImage image;
	wxImage rendImage;
	bool ratioFit;
private:
	void onScroll(wxMouseEvent& evt);
	void fitToRatio(wxImage image, int neww, int newh);
	void panHandler(wxMouseEvent& evt);
	void leftDown(wxMouseEvent& evt);
	void leftUp(wxMouseEvent& evt);
	void render(wxDC& dc);
	void bgErase(wxEraseEvent& evt);
	void onSize(wxSizeEvent& evt);

public:
	ImagePanel(wxWindow* parent, wxString file, wxBitmapType format);
	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	wxDECLARE_EVENT_TABLE();
};

