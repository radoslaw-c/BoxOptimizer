#pragma once
#include <GL/glew.h>
#include <vector>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Primitive_T
{
public:
	Primitive_T(GLenum drawingMode);
	~Primitive_T();
	void Initialize();
	void Draw();

protected:
	// methods
	void CreateBuffers();
	void InitializeVertexArray();
	void InitializeBuffers();
	void BindBuffers();
	void UnbindBuffers();

	// fields
	unsigned int arrayBuffer{ 0 }; // buffer storing vertex data: pos, color etc
	unsigned int vertexArray{ 0 }; // buffer storing data layout of array buffer and the array buffer itself
	unsigned int elementArrayBuffer{ 0 };	//buffer storing relations between vertices for drawing
	std::array<unsigned int, 2> buffers{ 0,0 };

	// fields - data
	std::vector<float> vertexData;	// buffer storing vertex-related information, such as positions and/or color
	std::vector<unsigned int> elementBuffer;	// buffer storing relations between vertices to be drawn

private:
	GLenum drawingMode;
};

