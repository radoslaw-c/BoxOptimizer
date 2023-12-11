#include "screenObjects\Primitive_T.h"
#include <iostream>


Primitive_T::Primitive_T(GLenum drawingMode)
{
	this->drawingMode = drawingMode;
}

Primitive_T::~Primitive_T()
{
	glDeleteBuffers(2, buffers.data());
}

void Primitive_T::Initialize()
{
	//CreateBuffers();
	//InitializeVertexArray();
	//InitializeBuffers();

	// TODO maybe some cleanup later on? 
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &arrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &elementArrayBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementBuffer.size() * sizeof(unsigned int),
		elementBuffer.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Primitive_T::Draw()
{
	BindBuffers();
	glDrawElements(drawingMode, elementBuffer.size(), GL_UNSIGNED_INT, 0);
}

void Primitive_T::CreateBuffers()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glGenBuffers(2, buffers.data());

	arrayBuffer = buffers[0];
	elementArrayBuffer = buffers[1];
}

void Primitive_T::InitializeVertexArray()
{
	glBindVertexArray(vertexArray);

	// vertex data -- position
	// TODO add 4th dimmension to position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
		(void*)0);
	glEnableVertexAttribArray(0);

	// vertex data -- color
	// NOTE: may need adding alfa channel
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
		(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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
