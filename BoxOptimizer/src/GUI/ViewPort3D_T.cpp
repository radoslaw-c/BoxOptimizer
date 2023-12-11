#include "ViewPort3D_T.h"

ViewPort3D_T::ViewPort3D_T(wxWindow* parent, const wxGLAttributes& canvasAttrs) :
	wxGLCanvas(parent, canvasAttrs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS)
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

	// bind for keyboard events
	Bind(wxEVT_KEY_DOWN, &ViewPort3D_T::OnKeyDown, this);
	// and mouse events as well
	Bind(wxEVT_MOTION, &ViewPort3D_T::OnMouseMoved, this);
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
		layout (location = 1) in vec3 aColor;

		uniform mat4 modelMatrix;
		uniform mat4 cameraMatrix;
		uniform mat4 projectionMatrix;

		out vec3 vertexColor;

		void main()
		{
			gl_Position = projectionMatrix * cameraMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
			vertexColor = aColor;
		}
	)";

	constexpr auto fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;

		in vec3 vertexColor;

		void main()
		{
			FragColor = vec4(vertexColor, 1.0f);
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

	FindUniforms();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	WorldGrid.Initialize();
	Element.Initialize();
	Element2.Initialize();

	isOpenGLInitialized = true;
	return true;
}

void ViewPort3D_T::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc = wxPaintDC(this);

	if (!isOpenGLInitialized)
		return;

	SetCurrent(*openGLContext);
	
	// check for image depth
	GLint depthFuncValue;
	glGetIntegerv(GL_DEPTH_FUNC, &depthFuncValue);
	glClearDepth(depthFuncValue == GL_LEQUAL ? 0.0f : 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);

	ApplyTransformations();

	WorldGrid.Draw();
	Element.Draw();
	Element2.Draw();

	SwapBuffers();
}

void ViewPort3D_T::OnSize(wxSizeEvent& event)
{
	bool firstApperance = IsShownOnScreen() && !isOpenGLInitialized;

	if (firstApperance)
		InitializeOpenGL();

	if (isOpenGLInitialized)
	{
		viewPortSize = event.GetSize() * GetContentScaleFactor();
		glViewport(0, 0, viewPortSize.x, viewPortSize.y);
	}

	event.Skip();
}

void ViewPort3D_T::FindUniforms()
{
	// TODO add check for -1 -- invalid OR not found

	u_modelMatrix = glGetUniformLocation(shaderProgram, "modelMatrix");
	u_cameraMatrix = glGetUniformLocation(shaderProgram, "cameraMatrix");
	u_projectionMatrix = glGetUniformLocation(shaderProgram, "projectionMatrix");
}

void ViewPort3D_T::OnKeyDown(wxKeyEvent& event)
{
	const float cameraSpeed = 0.5f;
	// TODO solve directions
	switch (event.GetKeyCode())
	{
	case 'W':
		cameraPos += cameraSpeed * cameraFront;
		break;

	case 'A':
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		break;

	case 'S':
		cameraPos -= cameraSpeed * cameraFront;
		break;

	case 'D':
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		break;


	case 'R':
		cameraPos = glm::vec3(1.0f, 1.0f, 1.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
		break;

	default:
		event.Skip();
		break;
	}

	Refresh();
}

void ViewPort3D_T::OnMouseMoved(wxMouseEvent& event)
{
	wxPoint mousePos = wxGetMousePosition();

	if (wxGetMouseState().MiddleIsDown() && !wxGetKeyState(WXK_CONTROL) &&
		!wxGetKeyState(WXK_SHIFT))
	{
		const float sensivity = 0.3f;
		const auto pivotPoint = glm::vec4(cameraFront, 1.0f);
		const float delta_x = (prevMousePos.x - mousePos.x) * sensivity;
		
		auto tempPos = glm::vec4(cameraPos, 1.0f);
		const float delta_y = (prevMousePos.y - mousePos.y) * sensivity;

		auto rotationQuat1 = glm::angleAxis(glm::radians(delta_x), glm::vec3(0.0f, 1.0f, 0.0f));

		auto rotVector = glm::cross((cameraPos - cameraFront), glm::vec3(0.0f, 1.0f, 0.0f));
		auto rotationQuat2 = glm::angleAxis(glm::radians(-1.0f * delta_y), rotVector);
		
		auto rotationQuat = rotationQuat2 * rotationQuat1;
		auto rotateMatrix = glm::mat4_cast(rotationQuat);

		tempPos = (rotateMatrix * (tempPos - pivotPoint)) + pivotPoint;

		cameraPos = tempPos;
	}

	if (wxGetMouseState().MiddleIsDown() && wxGetKeyState(WXK_SHIFT) && 
		!wxGetKeyState(WXK_CONTROL))
	{
		 const float sensivity = 0.001f;
		 const float delta_x = (prevMousePos.x - mousePos.x) * sensivity;
		 const float delta_y = (prevMousePos.y - mousePos.y) * sensivity;
		 const auto lookVector = glm::normalize(cameraPos - cameraFront);
		 
		 auto mat = glm::mat4(1.0f);
		 auto horizTransVector = glm::cross(lookVector, glm::vec3(0.0f, 1.0f, 0.0f));
		 horizTransVector = glm::normalize(horizTransVector);
		 mat = glm::translate(mat, horizTransVector * -delta_x);
		 
		 auto mat2 = glm::mat4(1.0f);
		 auto vec1 = glm::cross(lookVector, horizTransVector);
		 mat2 = glm::translate(mat, vec1 * delta_y);

		 cameraFront = mat2 * glm::vec4(cameraFront, 1.0f);
		 cameraPos = mat2 * glm::vec4(cameraPos, 1.0f);
	}
	
	if (wxGetMouseState().MiddleIsDown() && wxGetKeyState(WXK_CONTROL) &&
		!wxGetKeyState(WXK_SHIFT))
	{
		
	}

	prevMousePos = mousePos;
	Refresh();
}

void ViewPort3D_T::ApplyTransformations()
{
	auto cameraMatrix = glm::lookAt(cameraPos, cameraFront, cameraUp);

	 glUniformMatrix4fv(u_cameraMatrix, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	//glUniformMatrix4fv(u_cameraMatrix, 1, GL_FALSE, glm::value_ptr(newCameraMat));

	// projection matrix
	auto projectionMatrix = glm::perspective(glm::radians(45.0f), (float)viewPortSize.x / (float)viewPortSize.y,
		0.1f, 1000.0f);

	glUniformMatrix4fv(u_projectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}
