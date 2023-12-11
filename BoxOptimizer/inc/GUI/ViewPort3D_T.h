#pragma once
#include <wx/wx.h>
#include <GL/glew.h>
#include <wx/glcanvas.h>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube_T
{
public:
	Cube_T()
	{

	}
	static constexpr auto vertices = std::array
	{
		// front
		-0.05f, -0.05f, -0.05f, 1.0f, 0.0f, 0.0f, // 0
		 0.05f, -0.05f, -0.05f, 1.0f, 0.0f, 0.0f,  // 1
		 0.05f,  0.05f, -0.05f, 1.0f, 0.0f, 0.0f,   // 2
		-0.05f,  0.05f, -0.05f, 1.0f, 0.0f, 0.0f,  // 3

		// top
		-0.05f, 0.05f, -0.05f, 0.0f, 0.0f, 1.0f, // 4
		 0.05f, 0.05f, -0.05f, 0.0f, 0.0f, 1.0f,  // 5
		 0.05f, 0.05f,  0.05f, 0.0f, 0.0f, 1.0f,   // 6
		-0.05f, 0.05f,  0.05f, 0.0f, 0.0f, 1.0f,  // 7

		// left
		-0.05f, -0.05f, -0.05f, 0.0f, 1.0f, 0.0f, // 8
		-0.05f,  0.05f, -0.05f, 0.0f, 1.0f, 0.0f,  // 9
		-0.05f,  0.05f,  0.05f, 0.0f, 1.0f, 0.0f,   // 10
		-0.05f, -0.05f,  0.05f, 0.0f, 1.0f, 0.0f,  // 11

		// right
		0.05f, -0.05f, -0.05f, 0.5f, 0.5f, 0.5f, // 12
		0.05f,  0.05f, -0.05f, 0.5f, 0.5f, 0.5f,  // 13
		0.05f,  0.05f,  0.05f, 0.5f, 0.5f, 0.5f,   // 14
		0.05f, -0.05f,  0.05f, 0.5f, 0.5f, 0.5f,  // 15

		// back
		-0.05f, -0.05f, 0.05f, 0.7f, 0.7f, 0.7f, // 16
		 0.05f, -0.05f, 0.05f, 0.7f, 0.7f, 0.7f,  // 17
		 0.05f,  0.05f, 0.05f, 0.7f, 0.7f, 0.7f,   // 18
		-0.05f,  0.05f, 0.05f, 0.7f, 0.7f, 0.7f,  // 19

		// bottom
		-0.05f, -0.05f,  0.05f, 0.3f, 0.3f, 0.3f, // 20
		 0.05f, -0.05f,  0.05f, 0.3f, 0.3f, 0.3f,  // 21
		 0.05f, -0.05f, -0.05f, 0.3f, 0.3f, 0.3f, // 22
		-0.05f, -0.05f, -0.05f, 0.3f, 0.3f, 0.3f // 23

	};

	static constexpr auto elementBuffer = std::array
	{
		// front
		0, 1, 2, // first triangle
		2, 3, 0, // second triangle

		// top
		4, 5, 6, // first triangle
		6, 7, 4, // second triangle

		// left
		8, 9, 10,  // first triangle
		10, 11, 8, // second triangle

		// right
		14, 13, 12, // 12, 13, 14, // first triangle
		12, 15, 14, // 14, 15, 12, // second triangle

		// back
		18, 17, 16, // 16, 17, 18, // first triangle
		16, 19, 18, // 18, 19, 16, // second triangle

		// bottom
		20, 21, 22, // first triangle
		22, 23, 20  // second triangle
	};
};

class Grid_T
{
public:
	Grid_T();

	std::vector<float> vertexArray;
	std::vector<unsigned int> elementBuffer;

private:
	int numberOfVerts = 100;
	int maxDist = 50; //dist range <-1000; 1000>
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
	Grid_T grid = Grid_T();

	GLint u_modelMatrix{ -1 };
	GLint u_cameraMatrix{ -1 };
	GLint u_projectionMatrix{ -1 };

	wxSize viewPortSize;

	unsigned int VAO{ 0 }, VBO{ 0 }, EBO{ 0 }, shaderProgram{ 0 };
	unsigned int gridVertexBuffer{ 0 }, gridVertexAttribObj{ 0 },
		gridElementBuffer{ 0 };

	float angle_x{ 0 }, angle_y{ 0 };

	//methods
	void FindUniforms();
	void OnKeyDown(wxKeyEvent& event);

	void ApplyTransformations();
};


