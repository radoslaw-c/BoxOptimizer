#pragma once
#include <wx/wx.h>
#include <wx/splitter.h>
#include <fstream>

#include "ViewPort3D_T.h"
#include "CSVParser_T.h"

class MainFrame_T : public wxFrame
{
public:
	MainFrame_T(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
	ViewPort3D_T* ViewPort3D{ nullptr };
	CSVParser_T DataParser;
	
	wxDECLARE_EVENT_TABLE();

	// event handling methods
	void LoadDataFromCSV(wxCommandEvent& e);
};

enum buttonIds 
{
	LOAD_DATA_BUTTON_ID = wxID_LAST + 1
};

