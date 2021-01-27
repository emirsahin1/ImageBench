#include "App.h"
#include "Theme.h"


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
	mainWindow->SetBackgroundColour(BACKGROUND_COLOR);
	mainWindow->Show();
	//mainWindow->m_flSelector->ShowModal();

	return true;
}
