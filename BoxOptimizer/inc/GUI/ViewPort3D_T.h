#pragma once
#include <wx/wx.h>
#include <GL/glew.h>
#include <wx/glcanvas.h>

class ViewPort3D_T : public wxGLCanvas
{
public:
	ViewPort3D_T(wxWindow* parent, const wxGLAttributes& canvasAttrs);
	~ViewPort3D_T();

	bool InitializeOpenGLFunctions();
	bool InitializeOpenGL();

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);

private:
	wxGLContext* openGLContext{ NULL };
	bool isOpenGLInitialized{ false };

	unsigned int VAO{ 0 }, VBO{ 0 }, shaderProgram{ 0 };
};

