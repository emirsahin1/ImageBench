#include "MainW.h"
#include <wx/splitter.h>

wxBEGIN_EVENT_TABLE(MainW, wxFrame)
	EVT_BUTTON(1001, OnButtonClicked)
wxEND_EVENT_TABLE()


MainW::MainW() : wxFrame(nullptr, wxID_ANY, "Green Screen Remover", wxPoint(0,0), wxGetDisplaySize())
{
	//hBox = new wxBoxSizer(wxHORIZONTAL);
	//hBox->Add(m_btn1, wxEXPAND);
	//hBox->Add(m_lstbox, wxEXPAND);
	//mainPanel->SetSizer(hBox);
	
	//SetDoubleBuffered(true);
	wxSplitterWindow* mainSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
															wxSP_BORDER | wxSP_LIVE_UPDATE);

	wxPanel* rightPanel = new wxPanel(mainSplitter, wxID_ANY, wxDefaultPosition);
	ImagePanel* imagePanel = new ImagePanel(mainSplitter, wxT("BWcave.png"),wxBITMAP_TYPE_PNG);

	wxBoxSizer* l_vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* r_vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* r_hBox = new wxBoxSizer(wxHORIZONTAL);

	m_btn1 = new wxButton(rightPanel, 1001, "TEST");
	m_lstbox = new wxListBox(rightPanel, wxID_ANY);

	r_vBox->Add(m_btn1, 1, wxEXPAND, wxALIGN_CENTER);
	r_vBox->Add(m_lstbox, 1, wxEXPAND, wxALIGN_CENTER);

	rightPanel->SetSizer(r_vBox);

	mainSplitter->SetMinimumPaneSize(200);
	mainSplitter->SplitVertically(imagePanel, rightPanel);

	/*m_flSelector = new wxFileDialog(this, "Select an image", wxEmptyString, wxEmptyString, 
	"BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|PNG files (*.png)|*.png", wxFD_OPEN, wxDefaultPosition, wxSize(100,100));*/


	m_menuBar = new wxMenuBar();
	m_menu = new wxMenu();
	m_menu->Append(wxID_ANY, wxString("Save"));
	m_menuBar->Append(m_menu, wxString("File"));
	SetMenuBar(m_menuBar);
	//wxlayout
}

MainW::~MainW()
{
}

void MainW::OnButtonClicked(wxCommandEvent &evt)
{
	m_lstbox->AppendString("TEST");
	evt.Skip();
}
