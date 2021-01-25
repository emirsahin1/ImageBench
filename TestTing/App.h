#pragma once
#include <wx/wx.h>
#include "MainW.h"

class App : public wxApp
{
public:
	App();
	~App();
	bool OnInit() override;

	MainW* mainWindow = nullptr; 
};

