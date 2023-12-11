#pragma once
#include <wx/wx.h>
#include <GL/glew.h>
#include <wx/glcanvas.h>
#include <array>

class Cube_T
{
public:
	Cube_T()
	{

	}
	std::array<float, 12> vertices =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f


	};

	std::array<unsigned int, 6> elementBuffer =
	{
		0, 1, 2, 
		2, 3, 0
	};
};

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
	Cube_T testCube = Cube_T();

	unsigned int VAO{ 0 }, VBO{ 0 }, EBO{ 0 }, shaderProgram{ 0 };
};


