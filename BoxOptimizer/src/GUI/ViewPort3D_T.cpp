#include "ViewPort3D_T.h"

ViewPort3D_T::ViewPort3D_T(wxWindow* parent, const wxGLAttributes& canvasAttrs) :
	wxGLCanvas(parent, canvasAttrs)
{
	wxGLContextAttrs ctxAttrs;
	ctxAttrs.PlatformDefaults().CoreProfile().OGLVersion(3, 3).EndList();
	openGLContext = new wxGLContext(this, nullptr, &ctxAttrs);

	if (!openGLContext->IsOK())
	{
		wxMessageBox("This software requires an OpenGL 3.3 capable device.",
			"OpenGL version error", wxOK | wxICON_INFORMATION, this);
		delete openGLContext;
		openGLContext = nullptr;
	}

	// binding methods to events
	Bind(wxEVT_SIZE, &ViewPort3D_T::OnSize, this);
	Bind(wxEVT_PAINT, &ViewPort3D_T::OnPaint, this);
}

ViewPort3D_T::~ViewPort3D_T()
{
	delete openGLContext;
}

bool ViewPort3D_T::InitializeOpenGLFunctions()
{
	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		wxLogError("OpenGL GLEW initialization failed: %s",
			reinterpret_cast<const char*>(glewGetErrorString(err)));
		return false;
	}

	wxLogDebug("Status: Using GLEW: %s", reinterpret_cast<const char*>(glewGetString(GLEW_VERSION)));
	return true;
}

bool ViewPort3D_T::InitializeOpenGL()
{
	if (!openGLContext)
		return false;

	SetCurrent(*openGLContext);

	if (!InitializeOpenGLFunctions())
	{
		wxMessageBox("Error: Could not initialize OpenGL function pointers.",
			"OpenGL initialization error", wxOK | wxICON_INFORMATION);
		return false;
	}

	wxLogDebug("OpenGL versoin: %s", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	wxLogDebug("OpenGL vendor: %s", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));

	// vertex shader source
	// TODO to be moved to a separate shader class

	constexpr auto vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	constexpr auto fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
		void main()
		{
			FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
	)";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		wxLogDebug("Vertex shader compilation failed: %s", infoLog);
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		wxLogDebug("Vertex shader compilation failed: %s", infoLog);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		wxLogDebug("Shader program linking failed: %s", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//float vertices[] = 
	//{
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 0.0f
	//};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, testCube.vertices.size() * sizeof(float), testCube.vertices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		testCube.elementBuffer.size() * sizeof(unsigned int),
		testCube.elementBuffer.data(), 
		GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	isOpenGLInitialized = true;
	return true;
}

void ViewPort3D_T::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc = wxPaintDC(this);

	if (!isOpenGLInitialized)
		return;

	SetCurrent(*openGLContext);
	
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	//glDrawArrays(GL_POINTS, 0, 4);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, testCube.elementBuffer.size(), GL_UNSIGNED_INT, 0);

	SwapBuffers();
}

void ViewPort3D_T::OnSize(wxSizeEvent& event)
{
	bool firstApperance = IsShownOnScreen() && !isOpenGLInitialized;

	if (firstApperance)
		InitializeOpenGL();

	if (isOpenGLInitialized)
	{
		auto viewPortSize = event.GetSize() * GetContentScaleFactor();
		glViewport(0, 0, viewPortSize.x, viewPortSize.y);
	}

	event.Skip();
}
