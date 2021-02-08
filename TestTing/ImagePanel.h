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
	wxBitmap rendImage;
private:
	void onScroll(wxMouseEvent& evt);
	void fitImageToRatio(int neww, int newh);
	void panHandler(wxMouseEvent& evt);
	void leftDown(wxMouseEvent& evt);
	void leftUp(wxMouseEvent& evt);
	void render(wxDC& dc);
	void bgErase(wxEraseEvent& evt);
	void onSize(wxSizeEvent& evt);
	void initImageProps();

public:
	ImagePanel(wxWindow* parent);
	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void loadImage(wxString path);
	void loadImage(uint8_t* imageData, int x, int y);
	void loadImage(uint8_t* imageData, uint8_t* alphaData, int x, int y);
	wxDECLARE_EVENT_TABLE();
};

