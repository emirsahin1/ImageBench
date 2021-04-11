#pragma once
#include <wx/wx.h>

class ImagePanel : public wxPanel
{
private:
	int canvw, canvh;
	float imgh, imgw, scale, aspRatio, imageOffsetX, imageOffsetY;
	int imagePosX, imagePosY;
	float mouseX, mouseY, panAmountX, panAmountY;
	bool isPanning, isLoading;
	wxCursor panCursor;
	wxImage image;
	wxImage loadingScreen;
	wxBitmap rendImage;
private:
	void onScroll(wxMouseEvent& evt);
	void fitImageToRatio(int neww, int newh);
	void panHandler(wxMouseEvent& evt);
	void leftDown(wxMouseEvent& evt);
	void leftUp(wxMouseEvent& evt);
	void rightDown(wxMouseEvent& evt);
	void rightUp(wxMouseEvent& evt);
	void drawAtMouse(wxMouseEvent& evt);
	void updateImage();
	void render(wxDC& dc);
	void renderLoading(wxDC& dc);
	void bgErase(wxEraseEvent& evt);
	void onSize(wxSizeEvent& evt);
	void initImageProps();
	void initBitmapProps(wxBitmap bitmap);
	wxBitmap* RGBAtoBitmap(unsigned char* rgba, int w, int h);

public:
	ImagePanel(wxWindow* parent);
	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void loadImage(wxString path);
	void loadImage(uint8_t* imageData, int x, int y, int channels);
	void loadImage(uint8_t* imageData, int x, int y);
	void loadImage(uint8_t* imageData, uint8_t* alphaData, int x, int y);
	void setLoading(bool isLoading);
	wxDECLARE_EVENT_TABLE();
};

