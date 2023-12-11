#include "MainFrame_T.h"

MainFrame_T::MainFrame_T(const wxString& title, const wxPoint& pos, const wxSize& size) :
	wxFrame(NULL, wxID_ANY, title, pos, size)
{
	auto* splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxSP_BORDER | wxSP_LIVE_UPDATE);

	auto* leftPanel_controls = new wxPanel(splitter);
	auto* rightpanel_3Dview = new wxPanel(splitter);

	//leftPanel_controls->SetBackgroundColour(wxColor(0xff, 0xfa, 0xfa, 0xfa));
	rightpanel_3Dview->SetBackgroundColour(wxColor(0xff, 0xee, 0xff));

	splitter->SetMinimumPaneSize(200);
	splitter->SetSashGravity(0.5f);

	splitter->SplitVertically(leftPanel_controls, rightpanel_3Dview);
}


