#pragma once
#include <wx/wx.h>
#include <wx/colordlg.h>
#include "ImagePanel.h"
#include "ImageProcessor.h"
#include "BrightnessFrame.h"
#include <wx/popupwin.h>

class MainW : public wxFrame
{
public:
	MainW();
	~MainW();
	wxDECLARE_EVENT_TABLE();

public:
	ImageProcessor imgProc;
	wxString imagePath;
	wxFileDialog* m_flSelector;
	wxColourDialog* r_clrDiag;

	BrightnessFrame* brightnessFrame;
	wxButton* r_btn_brightness;

	ImagePanel* imagePanel;
	wxButton* Test;
	wxBoxSizer* m_hBox;
	wxMenuBar* m_menuBar;
	wxMenu* fileMenu;
	wxMenu* editMenu;
	wxMenu* settingsMenu;

	wxPanel* rightPanel;
	wxBoxSizer* r_vBox;
	wxButton* r_btn1;
	wxButton* r_btn2;
	wxButton* r_btn3;
	wxButton* r_btn4;
	wxListBox* r_lstbox; 
	wxCheckBox* r_prevCheckBox; 


	void RemoveGreenScreen(wxCommandEvent& evt);
	void InvertImage(wxCommandEvent& evt);
	void GrayScaleImage(wxCommandEvent& evt);
	void ChangeBrightness(wxScrollEvent& evt);
	void OpenBrightnessFrame(wxCommandEvent& evt);
	void LoadImageButton(wxCommandEvent &evt);
	void SaveImage(wxCommandEvent& evt);
	void HideWindow(wxCloseEvent& evt);

private:
	void CheckedRealTime(wxCommandEvent& evt);

	const int brightnessEvtID;
};

