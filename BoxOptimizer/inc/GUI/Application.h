#pragma once
#include <iostream>
#include <wx/wx.h>
#include "Solver.h"
#include "ConsoleVisualiser_T.h"
#include "MainFrame_T.h"

class App : public wxApp
{
public:
	bool OnInit();
};

//application entry point
wxIMPLEMENT_APP(App);
