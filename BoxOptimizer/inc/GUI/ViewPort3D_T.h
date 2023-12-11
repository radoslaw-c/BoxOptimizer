#pragma once
#include <wx/wx.h>
#include <GL/glew.h>
#include <wx/glcanvas.h>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "screenObjects/WorldGrid_T.h"
#include "screenObjects/Element_T.h"

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

	GLint u_modelMatrix{ -1 };
	GLint u_cameraMatrix{ -1 };
	GLint u_projectionMatrix{ -1 };

	wxSize viewPortSize;

	unsigned int VAO{ 0 }, VBO{ 0 }, EBO{ 0 }, shaderProgram{ 0 };
	unsigned int gridVertexBuffer{ 0 }, gridVertexAttribObj{ 0 },
		gridElementBuffer{ 0 };

	glm::vec3 cameraPos = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	wxPoint prevMousePos;
	float yaw = 0, pitch = 0;

	// screen objects
	WorldGrid_T WorldGrid;
	GUIObjects::Element_T Element = GUIObjects::Element_T(0.0f, 0.0f, 0.0f);
	GUIObjects::Element_T Element2 = GUIObjects::Element_T(0.0f, 0.05f, 0.0f);;

	//methods
	void FindUniforms();
	void OnKeyDown(wxKeyEvent& event);
	void OnMouseMoved(wxMouseEvent& event);

	void ApplyTransformations();
};


