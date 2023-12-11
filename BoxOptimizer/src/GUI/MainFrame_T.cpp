#include "MainFrame_T.h"

MainFrame_T::MainFrame_T(const wxString& title, const wxPoint& pos, const wxSize& size) :
	wxFrame(NULL, wxID_ANY, title, pos, size)
{
	InitializeUI();
}

void MainFrame_T::LoadDataFromCSV(wxCommandEvent& e)
{
	auto fileDialog = wxFileDialog(this, ("Open data file"), "", "", "CSV files (*.csv) | *.csv",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	if (fileDialog.ShowModal() == wxID_CANCEL)
		return;

	auto dataFilePath = std::string(fileDialog.GetPath().mb_str());
	DataParser = CSVParser_T(dataFilePath);

	TextCtrls.dataPathTextCntrl->ChangeValue(dataFilePath);
}

void MainFrame_T::FindSolutions(wxCommandEvent& e)
{
	auto mainSolver = Solver_T();
	//mainSolver.InitializeElementsManually();
	mainSolver.LoadElementData(DataParser.DataFrame());
	Solution = mainSolver.Solve();

	ViewPort3D->DrawSolution(Solution);
}

void MainFrame_T::InitializeUI()
{
	mainSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxSP_BORDER | wxSP_LIVE_UPDATE);
	wxGLAttributes vAttrs;
	vAttrs.PlatformDefaults().Defaults().EndList();

	if (wxGLCanvas::IsDisplaySupported(vAttrs))
	{
		ViewPort3D = new ViewPort3D_T(mainSplitter, vAttrs);
		ViewPort3D->SetMinSize(FromDIP(wxSize(640, 480)));
	}

	mainSplitter->SetMinimumPaneSize(300);
	mainSplitter->SetSashGravity(0.0f);

	controlsPanel = new wxPanel(mainSplitter);
	PolulateControlsPanel();
	mainSplitter->SplitVertically(controlsPanel, ViewPort3D);
}

void MainFrame_T::PolulateControlsPanel()
{
	PopulateDataLoadingArea();
	PopulateResultsArea();

	controlsPanel->SetSizer(Sizers.mainVerticalSizer);
	controlsPanel->SetBackgroundColour(wxColor(0xd9, 0xdd, 0xdc));
}

void MainFrame_T::PopulateDataLoadingArea()
{
	StaticBoxes.dataLoading = new wxStaticBox(controlsPanel, wxID_ANY, "Load data to solve");
	wxStaticBoxSizer* dataLoadingSizer = new wxStaticBoxSizer(StaticBoxes.dataLoading, wxHORIZONTAL);

	Buttons.loadDataButton = new wxButton(StaticBoxes.dataLoading, LOAD_DATA_BUTTON_ID, "Load csv data");
	dataLoadingSizer->Add(Buttons.loadDataButton);

	TextCtrls.dataPathTextCntrl = new wxTextCtrl(controlsPanel, DATA_PATH_TXTCTRL_ID, 
		wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	dataLoadingSizer->Add(TextCtrls.dataPathTextCntrl, 1, wxLEFT | wxEXPAND, 5);

	Sizers.mainVerticalSizer->Add(dataLoadingSizer, 0, wxEXPAND);
}

void MainFrame_T::PopulateResultsArea()
{
	StaticBoxes.results = new wxStaticBox(controlsPanel, wxID_ANY, "Results");
	wxStaticBoxSizer* verticalResultsSizer = new wxStaticBoxSizer(StaticBoxes.results, wxVERTICAL);

	Buttons.solveProblemButton = new wxButton(controlsPanel, SOLVE_BUTTON_ID, "Solve!");
	verticalResultsSizer->Add(Buttons.solveProblemButton);

	Sizers.mainVerticalSizer->Add(verticalResultsSizer, 0, wxEXPAND);
}

wxBEGIN_EVENT_TABLE(MainFrame_T, wxFrame)
EVT_BUTTON(LOAD_DATA_BUTTON_ID, MainFrame_T::LoadDataFromCSV)
EVT_BUTTON(SOLVE_BUTTON_ID, MainFrame_T::FindSolutions)
wxEND_EVENT_TABLE()
