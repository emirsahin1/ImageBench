#include "App.h"

wxIMPLEMENT_APP(App);

App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
	wxInitAllImageHandlers();
	mainWindow = new MainW();
	mainWindow->Maximize(true);
	mainWindow->Show();
	//mainWindow->m_flSelector->ShowModal();

	return true;
}
