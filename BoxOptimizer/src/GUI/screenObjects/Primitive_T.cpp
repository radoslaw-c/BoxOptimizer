#include "screenObjects\Primitive_T.h"
#include <iostream>


Primitive_T::Primitive_T(GLenum drawingMode)
{
	CreateBuffers();
	InitializeVertexArray();

}

Primitive_T::~Primitive_T()
{
	glDeleteBuffers(2, buffers.data());
}

void Primitive_T::Draw()
{
	BindBuffers();
	glDrawElements(drawingMode, vertexData.size(), GL_UNSIGNED_INT, 0);

}

void Primitive_T::CreateBuffers()
{
	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(2, buffers.data());

	arrayBuffer = buffers[0];
	elementArrayBuffer = buffers[1];
}

void Primitive_T::InitializeVertexArray()
{
	glBindVertexArray(vertexArray);

	// TODO add rest of that function, probably dependent on a specific type tho
}

void Primitive_T::InitializeBuffers()
{
	BindBuffers();

	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float),
		vertexData.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementBuffer.size() * sizeof(unsigned int),
		elementBuffer.data(), GL_STATIC_DRAW);

	UnbindBuffers();
}

void Primitive_T::BindBuffers()
{
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
}

void Primitive_T::UnbindBuffers()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
