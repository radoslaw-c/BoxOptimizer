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
}

void MainFrame_T::PolulateControlsPanel()
{
	
	Sizers.arrangeControlsSizer = new wxBoxSizer(wxHORIZONTAL);
	Buttons.loadDataButton = new wxButton(controlsPanel, LOAD_DATA_BUTTON_ID, "Load csv data");
	Buttons.solveProblemButton = new wxButton(controlsPanel, SOLVE_BUTTON_ID, "Solve!");

	TextCtrls.dataPathTextCntrl = new wxTextCtrl(controlsPanel, DATA_PATH_TXTCTRL_ID);

	StaticBoxes.dataLoading = new wxStaticBox(controlsPanel, wxID_ANY, "Load data to solve");

	Sizers.arrangeControlsSizer->Add(TextCtrls.dataPathTextCntrl, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
	Sizers.arrangeControlsSizer->Add(Buttons.loadDataButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
	Sizers.arrangeControlsSizer->Add(Buttons.solveProblemButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
	Sizers.arrangeControlsSizer->Add(StaticBoxes.dataLoading, 0, wxLEFT | wxTOP | wxBOTTOM, 5);

	controlsPanel->SetSizer(Sizers.arrangeControlsSizer);

	controlsPanel->SetBackgroundColour(wxColor(0xd9, 0xdd, 0xdc));
	mainSplitter->SplitVertically(controlsPanel, ViewPort3D);
}

wxBEGIN_EVENT_TABLE(MainFrame_T, wxFrame)
EVT_BUTTON(LOAD_DATA_BUTTON_ID, MainFrame_T::LoadDataFromCSV)
EVT_BUTTON(SOLVE_BUTTON_ID, MainFrame_T::FindSolutions)
wxEND_EVENT_TABLE()
