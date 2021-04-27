#include "MainW.h"
#include <wx/splitter.h>
#include <wx/colordlg.h>
#include "Theme.h"
#include "ImageProcessor.h"

wxBEGIN_EVENT_TABLE(MainW, wxFrame)
	EVT_BUTTON(1001, LoadImageButton)
	EVT_BUTTON(1002, RemoveGreenScreen)
	EVT_BUTTON(1003, InvertImage)
	EVT_CHECKBOX(1004, CheckedRealTime)
	EVT_MENU(2001, SaveImage)
wxEND_EVENT_TABLE()

MainW::MainW() : wxFrame(nullptr, wxID_ANY, "Green Screen Remover", wxPoint(0,0), wxGetDisplaySize()), imgProc(wxBitmap())
{
	//Menu Bar
	m_menuBar = new wxMenuBar();
	m_menu = new wxMenu();
	m_menu->Append(2001, wxString("Save"));
	m_menuBar->Append(m_menu, wxString("File"));
	SetMenuBar(m_menuBar);

	//Main Horizontal Box containing the imagePanel and rightPanel UI//
	rightPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	imagePanel = new ImagePanel(this);
	m_hBox = new wxBoxSizer(wxHORIZONTAL);
	m_hBox->Add(imagePanel, 5, wxEXPAND);
	m_hBox->Add(rightPanel, 2, wxEXPAND);

	//The vertical box inside the right panel//
	r_btn1 = new wxButton(rightPanel, 1001, "Open Image", wxDefaultPosition, wxDefaultSize);
	r_btn2 = new wxButton(rightPanel, 1002, "Remove Green", wxDefaultPosition, wxDefaultSize);
	r_btn3 = new wxButton(rightPanel, 1003, "Invert Image", wxDefaultPosition, wxDefaultSize);
	r_lstbox = new wxListBox(rightPanel, wxID_ANY);
	r_clrDiag = new wxColourDialog(rightPanel, NULL);
	r_prevCheckBox = new wxCheckBox(rightPanel, 1004, wxString("Real Time Preview"));
	r_prevCheckBox->SetForegroundColour(wxColor("white"));
	r_prevCheckBox->SetFont(r_prevCheckBox->GetFont().MakeLarger().MakeBold());
	
	r_vBox = new wxBoxSizer(wxVERTICAL);
	r_vBox->Add(r_btn1, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);
	r_vBox->Add(r_lstbox, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);
	r_vBox->Add(r_prevCheckBox, 0, wxALIGN_LEFT | wxALL | wxEXPAND, 20);
	r_vBox->Add(r_btn3, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);
	r_vBox->Add(r_btn2, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);
	rightPanel->SetMaxSize(wxSize(300, 1000));
	rightPanel->SetSizer(r_vBox);
	this->SetSizer(m_hBox);

	imgProc.BindPanel(imagePanel);
	
	m_flSelector = new wxFileDialog(this, "Select an image", wxEmptyString, wxEmptyString,
		"PNG files (*.png)|*.png", wxFD_OPEN, wxDefaultPosition, wxSize(100, 100));

	m_menuBar->SetBackgroundColour(BACKGROUND_COLOR);
	rightPanel->SetBackgroundColour(PANEl_BACKGROUND_COLOR);
	imagePanel->SetBackgroundColour(BACKGROUND_COLOR);
}

MainW::~MainW()
{
}

void MainW::LoadImageButton(wxCommandEvent &evt)
{
	r_lstbox->AppendString("Opening File:");
	m_flSelector->ShowModal();
	imagePath = m_flSelector->GetPath();
	if (imagePath.empty()) {
		r_lstbox->AppendString("Empty Path");
	}
	else {
		imagePanel->setLoading(true);
		Refresh();
		Update();
		r_lstbox->AppendString(imagePath);
		wxLogNull logNo; 
		//imgProc.loadImageDataRGBA(imagePath);
		//cout << pixelTest.r << " " << pixelTest.b << " " << pixelTest.g << "\n";
		//cout << imgProc.getPixel(1, 1);
		//cout << imgProc.getPixel(102, 102);
		/*if(imgProc.imgAlpha == NULL){
			imagePanel->loadImage(imgProc.imgData, imgProc.imageWidth, imgProc.imageHeight);
		}
		else {
			imagePanel->loadImage(imgProc.imgData, imgProc.imgAlpha, imgProc.imageWidth, imgProc.imageHeight);
		}*/
		imagePanel->loadBitmap(imagePath);
		imgProc.loadImageDataBMP(imagePanel->renderedBitmap);
		evt.Skip(); 
	}
}

void MainW::RemoveGreenScreen(wxCommandEvent& evt) {
	/*m_clrDiag->ShowModal();*/
	r_lstbox->AppendString("Removed Green Screen");
	imgProc.RemoveGreenScreen();
	imagePanel->Refresh();
}

void MainW::InvertImage(wxCommandEvent& evt) {
	/*m_clrDiag->ShowModal();*/
	r_lstbox->AppendString("Inverted Image");
	imgProc.InvertImage();
	imagePanel->Refresh();
}

void MainW::CheckedRealTime(wxCommandEvent& evt) {
	imgProc.prevRealtime = evt.IsChecked();
	evt.Skip();
}

void MainW::SaveImage(wxCommandEvent& evt) {
	if (imagePanel->renderedBitmap.IsNull()) {
		r_lstbox->AppendString("Error: No Image to save");
	}
	else {
		wxString filename = wxFileSelector("Save image as", wxEmptyString, wxEmptyString, ".png","PNG files (*.png)|*.png", wxFD_SAVE);

		wxImage imageSave = imagePanel->renderedBitmap.ConvertToImage();
		imageSave.SaveFile(filename);
	}
	
}