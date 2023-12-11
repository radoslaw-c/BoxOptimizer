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

	leftPanel->SetBackgroundColour(wxColor(0, 0, 255));

	mainSplitter->SetMinimumPaneSize(300);

	mainSplitter->SetSashGravity(0.5f);
	mainSplitter->SplitVertically(leftPanel, ViewPort3D);

	wxLogDebug("splitter size: %d x %d", mainSplitter->GetSize().x, mainSplitter->GetSize().y);
}
