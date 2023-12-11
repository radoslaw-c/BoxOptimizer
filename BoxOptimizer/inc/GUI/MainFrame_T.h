#pragma once
#include <wx/wx.h>
#include <wx/splitter.h>

#include "ViewPort3D_T.h"

class MainFrame_T : public wxFrame
{
public:
	MainFrame_T(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
	ViewPort3D_T* ViewPort3D{ nullptr };
};

