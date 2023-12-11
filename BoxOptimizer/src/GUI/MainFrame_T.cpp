#include "MainFrame_T.h"

MainFrame_T::MainFrame_T(const wxString& title, const wxPoint& pos, const wxSize& size) :
	wxFrame(NULL, wxID_ANY, title, pos, size)
{
	auto mainSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxSP_BORDER | wxSP_LIVE_UPDATE);

	wxGLAttributes vAttrs;
	vAttrs.PlatformDefaults().Defaults().EndList();
	
	if (wxGLCanvas::IsDisplaySupported(vAttrs))
	{
		ViewPort3D = new ViewPort3D_T(mainSplitter, vAttrs);
		ViewPort3D->SetMinSize(FromDIP(wxSize(640, 480)));
	}	

	auto* leftPanel = new wxPanel(mainSplitter);

	auto loadDataButton = new wxButton(leftPanel, LOAD_DATA_BUTTON_ID, "TEST");

	leftPanel->SetBackgroundColour(wxColor(0xd9, 0xdd, 0xdc));

	mainSplitter->SetMinimumPaneSize(300);

	mainSplitter->SetSashGravity(0.0f);
	mainSplitter->SplitVertically(leftPanel, ViewPort3D);

	wxLogDebug("splitter size: %d x %d", mainSplitter->GetSize().x, mainSplitter->GetSize().y);
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

wxBEGIN_EVENT_TABLE(MainFrame_T, wxFrame)
EVT_BUTTON(LOAD_DATA_BUTTON_ID, MainFrame_T::LoadDataFromCSV)
wxEND_EVENT_TABLE()
