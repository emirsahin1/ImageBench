#include "BrightnessFrame.h"
#include "Theme.h"

BrightnessFrame::BrightnessFrame(wxWindow* parent, int ID) : 
	wxFrame(parent, ID, "Brightness Control", wxDefaultPosition, wxDefaultSize,  wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP)
{
	this->SetBackgroundColour(BACKGROUND_COLOR);
	slider = new wxSlider(this, wxID_ANY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_LABELS | wxBORDER_SIMPLE | wxEXPAND);
	slider->SetForegroundColour("White");

}
