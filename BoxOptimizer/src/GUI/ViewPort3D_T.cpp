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

	// bind for keyboard events
	Bind(wxEVT_KEY_DOWN, &ViewPort3D_T::OnKeyDown, this);
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
			gl_Position = projectionMatrix * cameraMatrix *  modelMatrix *vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, testCube.vertices.size() * sizeof(float), testCube.vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		testCube.elementBuffer.size() * sizeof(unsigned int),
		testCube.elementBuffer.data(), 
		GL_STATIC_DRAW);
	




	 // pass grid data
	 glGenVertexArrays(1, &gridVertexAttribObj);
	 glBindVertexArray(gridVertexAttribObj);
	 
	 glGenBuffers(1, &gridVertexBuffer);
	 glBindBuffer(GL_ARRAY_BUFFER, gridVertexBuffer);
	 glBufferData(GL_ARRAY_BUFFER, grid.vertexArray.size() * sizeof(float), grid.vertexArray.data(), GL_STATIC_DRAW);
	 
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	 glEnableVertexAttribArray(0);
	 
	 glGenBuffers(1, &gridElementBuffer);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridElementBuffer);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	 	grid.elementBuffer.size() * sizeof(unsigned int),
	 	grid.elementBuffer.data(),
	 	GL_STATIC_DRAW);
	 
	 // colors
	 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	 glEnableVertexAttribArray(1);

	//// CreateBuffers()
	//glGenVertexArrays(1, &gridVertexAttribObj);
	//glGenBuffers(1, &gridVertexBuffer);
	//glGenBuffers(1, &gridElementBuffer);
	//
	////InitializeVertexArray()
	//glBindVertexArray(gridVertexAttribObj);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//
	////InitializeBuffers()
	//glBindVertexArray(gridVertexAttribObj);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridElementBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, gridVertexBuffer);
	//
	//glBufferData(GL_ARRAY_BUFFER, grid.vertexArray.size() * sizeof(float), grid.vertexArray.data(), GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	//	grid.elementBuffer.size() * sizeof(unsigned int),
	//	grid.elementBuffer.data(),
	//	GL_STATIC_DRAW);



	// unbind buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	FindUniforms();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	WorldGrid.Initialize();

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

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, testCube.elementBuffer.size(), GL_UNSIGNED_INT, 0);

	//glBindVertexArray(gridVertexAttribObj);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridElementBuffer);
	//glDrawElements(GL_POINTS, grid.elementBuffer.size(), GL_UNSIGNED_INT, 0);

	WorldGrid.Draw();


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
	// TODO solve directions
	switch (event.GetKeyCode())
	{
	case 'D':
		angle_y -= 5.0f;
		break;
	
	case 'A':
		angle_y += 5.0f;
		break;

	case 'W':
		angle_x += 5.0f;
		break;

	case 'S':
		angle_x -= 5.0f;
		break;

	default:
		event.Skip();
		break;
	}

	Refresh();
}

void ViewPort3D_T::ApplyTransformations()
{
	// model matrix
	// TODO probably won't be needed in the (more) final version of the software
	auto modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle_x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle_y), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(u_modelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// view matrix --- seems to be replaced by camera matrix

	// camera matrix
	auto cameraMatrix = glm::lookAt(glm::vec3(0.0f, 5.0f, 1.1f), glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(u_cameraMatrix, 1, GL_FALSE, glm::value_ptr(cameraMatrix));

	// projection matrix
	auto projectionMatrix = glm::perspective(glm::radians(45.0f), (float)viewPortSize.x / (float)viewPortSize.y,
		0.1f, 100.0f);

	glUniformMatrix4fv(u_projectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

Grid_T::Grid_T()
{
	vertexArray.resize(numberOfVerts * numberOfVerts * 6);
	elementBuffer.resize(numberOfVerts * numberOfVerts * 2);

	float step = 2 * (float)maxDist / (numberOfVerts - 1);

	for (int row = 0; row < numberOfVerts; ++row)
	{
		for (int column = 0; column < numberOfVerts; ++column)
		{
			auto x = -1 * maxDist + column * step;
			auto y = 0.0f;
			auto z = -1 * maxDist + row * step;

			auto r = 1.0f;
			auto g = 1.0f;
			auto b = 1.0;

			const auto vertexStrartIndex = (row * numberOfVerts + column) * 6;
			vertexArray[vertexStrartIndex + 0] = x;
			vertexArray[vertexStrartIndex + 1] = y;
			vertexArray[vertexStrartIndex + 2] = z;
			vertexArray[vertexStrartIndex + 3] = r;
			vertexArray[vertexStrartIndex + 4] = g;
			vertexArray[vertexStrartIndex + 5] = b;
		}
	}

	for (int idx = 0; idx < elementBuffer.size(); ++idx)
	{
		elementBuffer[idx] = idx;
	}
}
