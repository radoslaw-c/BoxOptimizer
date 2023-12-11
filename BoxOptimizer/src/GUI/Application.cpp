#include "Application.h"

bool App::OnInit()
{
	MainFrame_T* mainWindow = new MainFrame_T("Box Optimizer ALFA", wxDefaultPosition,
		wxDefaultSize);

	mainWindow->Show();
	return true;
}
