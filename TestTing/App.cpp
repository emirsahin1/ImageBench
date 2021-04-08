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
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	wxInitAllImageHandlers();
	mainWindow = new MainW();
	mainWindow->Maximize(true);
	mainWindow->SetBackgroundColour(BACKGROUND_COLOR);
	mainWindow->SetCursor(wxCursor(wxImage("CursorTest.png")));
	mainWindow->Show();

	return true;
}
