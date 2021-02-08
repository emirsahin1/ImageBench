#pragma once
#include <wx/wx.h>
#include "ImagePanel.h"

class MainW : public wxFrame
{
public:
	MainW();
	~MainW();
	wxDECLARE_EVENT_TABLE();

public:
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

	void OnButtonClicked(wxCommandEvent &evt);
};

