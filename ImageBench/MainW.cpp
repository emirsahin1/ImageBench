#include "MainW.h"
#include <wx/splitter.h>
#include <wx/colordlg.h>
#include "Theme.h"
#include "ImageProcessor.h" //TODO REMOVE THIS POSSIBKLY
#include <wx/popupwin.h>

wxBEGIN_EVENT_TABLE(MainW, wxFrame)
	EVT_MENU(2001, LoadImageButton)
	EVT_BUTTON(1001, LoadImageButton)
	EVT_MENU(3002, RemoveGreenScreen)
	EVT_MENU(3003, InvertImage)
	EVT_MENU(3001, OpenBrightnessFrame)
	EVT_MENU(3007, GrayScaleImage)
	EVT_CHECKBOX(1004, CheckedRealTime)
	EVT_MENU(1004, CheckedRealTime)
	EVT_COMMAND_SCROLL(1006, ChangeBrightness)
	EVT_MENU(2002, SaveImage)
	EVT_CLOSE(HideWindow)
wxEND_EVENT_TABLE()

MainW::MainW() : wxFrame(nullptr, wxID_ANY, "Green Screen Remover", wxPoint(0,0), wxGetDisplaySize()), imgProc(wxBitmap()), brightnessEvtID(1006)
{
	//Menu Bar
	m_menuBar = new wxMenuBar();
	fileMenu = new wxMenu();
	editMenu = new wxMenu();
	settingsMenu = new wxMenu();
	fileMenu->Append(2001, wxString("Load"));
	fileMenu->Append(2002, wxString("Save"));
	editMenu->Append(3001, wxString("Brightness"));
	editMenu->Append(3003, wxString("Invert"));
	editMenu->Append(3007, wxString("GrayScale HSP"));
	editMenu->Append(3002, wxString("Remove Green Screen"));
	settingsMenu->Append(1004, wxString("Realtime Preview"), wxEmptyString, wxITEM_CHECK);
	m_menuBar->Append(fileMenu, wxString("File"));
	m_menuBar->Append(editMenu, wxString("Edit Image"));
	m_menuBar->Append(settingsMenu, wxString("Settings"));
	SetMenuBar(m_menuBar);

	//Main Horizontal Box containing the imagePanel and rightPanel UI//
	rightPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	imagePanel = new ImagePanel(this);
	m_hBox = new wxBoxSizer(wxHORIZONTAL);
	m_hBox->Add(imagePanel, 5, wxEXPAND);
	m_hBox->Add(rightPanel, 2, wxEXPAND);

	//The vertical box inside the right panel//
	r_btn1 = new wxButton(rightPanel, 1001, "Open Image", wxDefaultPosition, wxDefaultSize);

	r_lstbox = new wxListBox(rightPanel, wxID_ANY);
	r_clrDiag = new wxColourDialog(rightPanel, NULL);
	r_prevCheckBox = new wxCheckBox(rightPanel, 1004, wxString("Real Time Preview"));
	r_prevCheckBox->SetForegroundColour(wxColor("white"));
	r_prevCheckBox->SetFont(r_prevCheckBox->GetFont().MakeLarger().MakeBold());
	
	r_vBox = new wxBoxSizer(wxVERTICAL);
	r_vBox->Add(r_lstbox, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);
	r_vBox->Add(r_prevCheckBox, 0, wxALIGN_LEFT | wxALL | wxEXPAND, 20);
	r_vBox->Add(r_btn1, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);


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
		std::cout << imgProc.getPixel(0, 0);
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

void MainW::GrayScaleImage(wxCommandEvent& evt) {
	r_lstbox->AppendString("GrayScale Image");
	imgProc.GrayScaleHSP();
	imagePanel->Refresh();
}

void MainW::ChangeBrightness(wxScrollEvent& evt) {

	imgProc.BrightnessControl(evt.GetPosition() / 5);
	
	/*brightnessPopup->SetSize(wxSize(500, 500));
	brightnessPopup->CentreOnParent();*/
	imagePanel->Refresh();
	evt.Skip();
}

void MainW::OpenBrightnessFrame(wxCommandEvent& evt) {
	brightnessFrame = new BrightnessFrame(this, wxID_ANY);
	brightnessFrame->slider->SetId(brightnessEvtID);
	brightnessFrame->Show();
	evt.Skip();
}

void MainW::CheckedRealTime(wxCommandEvent& evt) {
	imgProc.prevRealtime = evt.IsChecked();
	r_prevCheckBox->SetValue(evt.IsChecked());
	settingsMenu->Check(1004, evt.IsChecked());

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

void MainW::HideWindow(wxCloseEvent& evt) {
	Hide();
	evt.Skip();
}