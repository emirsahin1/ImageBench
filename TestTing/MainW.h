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
	wxString imagePath;
	wxFileDialog* m_flSelector;
	wxColourDialog* r_clrDiag;


	ImagePanel* imagePanel;
	wxBoxSizer* m_hBox;
	wxMenuBar* m_menuBar;
	wxMenu* m_menu; 

	wxPanel* rightPanel;
	wxBoxSizer* r_vBox;
	wxButton* r_btn1;
	wxButton* r_btn2;
	wxButton* r_btn3;
	wxListBox* r_lstbox; 
	wxCheckBox* r_prevCheckBox; 


	void RemoveGreenScreen(wxCommandEvent& evt);
	void InvertImage(wxCommandEvent& evt);
	void LoadImageButton(wxCommandEvent &evt);
	void SaveImage(wxCommandEvent& evt);

private:
	void CheckedRealTime(wxCommandEvent& evt);
};

