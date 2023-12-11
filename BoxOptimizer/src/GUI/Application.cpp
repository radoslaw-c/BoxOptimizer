#include "Application.h"

bool App::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	MainFrame_T* mainWindow = new MainFrame_T("Box Optimizer ALFA", wxDefaultPosition,
		wxSize(1280, 720));

	mainWindow->SetMinClientSize(wxSize(940, 480));
	mainWindow->Show();
	return true;
}
