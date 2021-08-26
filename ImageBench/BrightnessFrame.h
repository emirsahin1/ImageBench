#pragma once
#include <wx/wx.h>


class BrightnessFrame : public wxFrame {

public:
	BrightnessFrame(wxWindow* parent, int ID);

	wxSlider* slider;


};