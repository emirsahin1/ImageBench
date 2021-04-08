#include "MainW.h"
#include <wx/splitter.h>
#include "Theme.h"
#include "ImageProcessor.h"
#include <wx/colordlg.h>

wxBEGIN_EVENT_TABLE(MainW, wxFrame)
	EVT_BUTTON(1001, LoadImageButton)
	EVT_BUTTON(1002, ColorPickerButton)
wxEND_EVENT_TABLE()

MainW::MainW() : wxFrame(nullptr, wxID_ANY, "Green Screen Remover", wxPoint(0,0), wxGetDisplaySize())
{
	m_flSelector = new wxFileDialog(this, "Select an image", wxEmptyString, wxEmptyString,
	"PNG files (*.png)|*.png", wxFD_OPEN, wxDefaultPosition, wxSize(100, 100));
	//Main Horizontal Box containing the imagePanel and rightPanel UI//
	wxBoxSizer* m_hBox = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* rightPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	imagePanel = new ImagePanel(this);
	m_hBox->Add(imagePanel, 5, wxEXPAND);
	m_hBox->Add(rightPanel, 2, wxEXPAND);

	//The vertical box inside the right panel//
	wxBoxSizer* r_vBox = new wxBoxSizer(wxVERTICAL);
	m_btn1 = new wxButton(rightPanel, 1001, "Open Image", wxDefaultPosition, wxDefaultSize);
	wxButton* m_btn2 = new wxButton(rightPanel, 1002, "Remove Green", wxDefaultPosition, wxDefaultSize);
	m_clrDiag = new wxColourDialog(rightPanel, NULL);
	m_lstbox = new wxListBox(rightPanel, wxID_ANY);

	r_vBox->Add(m_btn1, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);
	r_vBox->Add(m_lstbox, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);
	r_vBox->Add(m_btn2, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);

	rightPanel->SetMaxSize(wxSize(300, rightPanel->GetMaxWidth()));
	rightPanel->SetSizer(r_vBox);
	this->SetSizer(m_hBox);

	//Menu Bar
	m_menuBar = new wxMenuBar();
	m_menu = new wxMenu();
	m_menu->Append(wxID_ANY, wxString("Save"));
	m_menuBar->Append(m_menu, wxString("File"));
	SetMenuBar(m_menuBar);
	
	m_menuBar->SetBackgroundColour(BACKGROUND_COLOR);
	rightPanel->SetBackgroundColour(PANEl_BACKGROUND_COLOR);
	imagePanel->SetBackgroundColour(BACKGROUND_COLOR);
}

MainW::~MainW()
{
}

void MainW::LoadImageButton(wxCommandEvent &evt)
{
	m_lstbox->AppendString("OpenFile");
	m_flSelector->ShowModal();
	imagePath = m_flSelector->GetPath();
	if (imagePath.empty()) {
		m_lstbox->AppendString("Empty Path");
	}
	else {
		imagePanel->setLoading(true);
		Refresh();
		Update();
		m_lstbox->AppendString(imagePath);
		wxLogNull logNo; 
		//imagePanel->loadImage(imagePath);
		ImageProcessor imgProc;
		imgProc.loadImage(imagePath);
		if(imgProc.imgAlpha == NULL){
		imagePanel->loadImage(imgProc.imgData, imgProc.imageWidth, imgProc.imageHeight);
		}
		else {
			imagePanel->loadImage(imgProc.imgData, imgProc.imgAlpha, imgProc.imageWidth, imgProc.imageHeight);
		}
		evt.Skip();
	}
}

void MainW::ColorPickerButton(wxCommandEvent& evt) {
	m_clrDiag->ShowModal();
}
