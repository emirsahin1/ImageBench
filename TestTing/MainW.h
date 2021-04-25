#pragma once
#include <wx/wx.h>
#include <wx/colordlg.h>
#include "ImagePanel.h"
#include "ImageProcessor.h"

class MainW : public wxFrame
{
public:
	MainW();
	~MainW();
	wxDECLARE_EVENT_TABLE();

public:
	ImageProcessor imgProc;
	ImagePanel* imagePanel = nullptr;
	wxString imagePath;
	wxBoxSizer* hBox = nullptr; 
	wxPanel* mainPanel = nullptr; 
	wxButton* m_btn1 = nullptr; 
	wxTextCtrl* m_txt1 = nullptr; 
	wxListBox* m_lstbox = nullptr; 
	wxFileDialog* m_flSelector;
	wxMenuBar* m_menuBar = nullptr; 
	wxMenu* m_menu = nullptr; 
	wxColourDialog* m_clrDiag = nullptr;
	void ColorPickerButton(wxCommandEvent& evt);
	void LoadImageButton(wxCommandEvent &evt);
};

