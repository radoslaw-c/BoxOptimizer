#pragma once
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/textctrl.h>
#include <fstream>

#include "ViewPort3D_T.h"
#include "CSVParser_T.h"
#include "Solver.h"

class MainFrame_T : public wxFrame
{
public:
	MainFrame_T(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
	ViewPort3D_T* ViewPort3D{ nullptr };
	CSVParser_T DataParser;
	Solution_T Solution;

	wxDECLARE_EVENT_TABLE();

	// event handling methods
	void LoadDataFromCSV(wxCommandEvent& e);
	void FindSolutions(wxCommandEvent& e);

	// GUI definition methods
	void InitializeUI();
	void PolulateControlsPanel();
	void PopulateDataLoadingArea();
	void PopulateResultsArea();

	// GUI elements
	wxSplitterWindow* mainSplitter{};
	wxPanel* controlsPanel{};

	struct Buttons_T
	{
		wxButton* loadDataButton{};
		wxButton* solveProblemButton{};
	};
	Buttons_T Buttons;
	
	struct StaticBoxes_T
	{
		wxStaticBox* dataLoading{};
		wxStaticBox* results{};
	};
	StaticBoxes_T StaticBoxes;

	struct Sizers_T
	{
		wxBoxSizer* mainVerticalSizer = new wxBoxSizer(wxVERTICAL);
	};
	Sizers_T Sizers;

	struct TextCtrls_T
	{
		wxTextCtrl* dataPathTextCntrl{};
	};
	TextCtrls_T TextCtrls;


};

enum buttonIds 
{
	LOAD_DATA_BUTTON_ID = wxID_LAST + 1,
	SOLVE_BUTTON_ID,
	DATA_PATH_TXTCTRL_ID
};

