#include "MainW.h"
#include <wx/splitter.h>
#include "Theme.h"

wxBEGIN_EVENT_TABLE(MainW, wxFrame)
	EVT_BUTTON(1001, OnButtonClicked)
wxEND_EVENT_TABLE()


MainW::MainW() : wxFrame(nullptr, wxID_ANY, "Green Screen Remover", wxPoint(0,0), wxGetDisplaySize())
{
	wxSplitterWindow* mainSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
															wxSP_NO_XP_THEME| wxSP_LIVE_UPDATE);

	wxPanel* rightPanel = new wxPanel(mainSplitter, wxID_ANY, wxDefaultPosition);
	ImagePanel* imagePanel = new ImagePanel(mainSplitter, wxT("BWcave.png"),wxBITMAP_TYPE_PNG);


	wxBoxSizer* l_vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* r_vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* r_hBox = new wxBoxSizer(wxHORIZONTAL);

	m_btn1 = new wxButton(rightPanel, 1001, "TEST");
	m_lstbox = new wxListBox(rightPanel, wxID_ANY);

	r_vBox->Add(m_btn1, 0, wxALIGN_TOP | wxALL | wxEXPAND | wxSHAPED, 30);
	r_vBox->Add(m_lstbox, 0, wxALIGN_CENTER | wxALL | wxEXPAND | wxSHAPED, 20);
	m_btn1->SetMaxSize(wxSize(500,100));

	rightPanel->SetSizer(r_vBox);

	mainSplitter->SetMinimumPaneSize(200);
	mainSplitter->SplitVertically(imagePanel, rightPanel);

	/*m_flSelector = new wxFileDialog(this, "Select an image", wxEmptyString, wxEmptyString, 
	"BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|PNG files (*.png)|*.png", wxFD_OPEN, wxDefaultPosition, wxSize(100,100));*/

	//Menu Bar
	m_menuBar = new wxMenuBar();
	m_menu = new wxMenu();
	m_menu->Append(wxID_ANY, wxString("Save"));
	m_menuBar->Append(m_menu, wxString("File"));
	
	
	
	m_menuBar->SetBackgroundColour(BACKGROUND_COLOR);
	rightPanel->SetBackgroundColour(BACKGROUND_COLOR);
	imagePanel->SetBackgroundColour(BACKGROUND_COLOR);
	mainSplitter->SetBackgroundColour(SASH_COLOR);
	SetMenuBar(m_menuBar);
}

MainW::~MainW()
{
}

void MainW::OnButtonClicked(wxCommandEvent &evt)
{
	m_lstbox->AppendString("TEST");
	evt.Skip();
}
