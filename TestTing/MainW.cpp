#include "MainW.h"
#include <wx/splitter.h>
#include "Theme.h"
#include "ImageProcessor.h"

wxBEGIN_EVENT_TABLE(MainW, wxFrame)
	EVT_BUTTON(1001, OnButtonClicked)
wxEND_EVENT_TABLE()


MainW::MainW() : wxFrame(nullptr, wxID_ANY, "Green Screen Remover", wxPoint(0,0), wxGetDisplaySize())
{
	wxBoxSizer* m_hBox = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* rightPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	imagePanel = new ImagePanel(this);

	wxBoxSizer* l_vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* r_vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* r_hBox = new wxBoxSizer(wxHORIZONTAL);

	m_btn1 = new wxButton(rightPanel, 1001, "Open Image", wxDefaultPosition, wxDefaultSize);
	m_lstbox = new wxListBox(rightPanel, wxID_ANY);

	m_hBox->Add(imagePanel, 5, wxEXPAND);
	m_hBox->Add(rightPanel, 2, wxEXPAND);

	r_vBox->Add(m_btn1, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);
	r_vBox->Add(m_lstbox, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);

	//m_btn1->SetMaxSize(wxSize(600,100));
	rightPanel->SetMaxSize(wxSize(300, rightPanel->GetMaxWidth()));
	rightPanel->SetBackgroundColour("red");
	rightPanel->SetSizer(r_vBox);
	this->SetSizer(m_hBox);


	m_flSelector = new wxFileDialog(this, "Select an image", wxEmptyString, wxEmptyString, 
	"PNG files (*.png)|*.png", wxFD_OPEN, wxDefaultPosition, wxSize(100,100));

	//Menu Bar
	m_menuBar = new wxMenuBar();
	m_menu = new wxMenu();
	m_menu->Append(wxID_ANY, wxString("Save"));
	m_menuBar->Append(m_menu, wxString("File"));
	
	m_menuBar->SetBackgroundColour(BACKGROUND_COLOR);
	rightPanel->SetBackgroundColour(PANEl_BACKGROUND_COLOR);
	imagePanel->SetBackgroundColour(BACKGROUND_COLOR);
	SetMenuBar(m_menuBar);
}

MainW::~MainW()
{
}

void MainW::OnButtonClicked(wxCommandEvent &evt)
{
	m_lstbox->AppendString("OpenFile");
	m_flSelector->ShowModal();
	imagePath = m_flSelector->GetPath();
	if (imagePath.empty()) {
		m_lstbox->AppendString("Empty Path");
	}
	else {
		m_lstbox->AppendString(imagePath);
		//imagePanel->loadImage(imagePath);
		Image img = removeGreenScreen(imagePath);
		if(img.imgAlpha == NULL){
			imagePanel->loadImage(img.imgData, img.x, img.y);
		}
		else {
			imagePanel->loadImage(img.imgData, img.imgAlpha, img.x, img.y);
		}
		evt.Skip();
	}
}
