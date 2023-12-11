#include "screenObjects/Element_T.h"

using GUIObjects::Element_T;
Element_T::Element_T(float pos_x, float pos_y, float pos_z,
	float width, float height, float length,
	unsigned int red, unsigned int green, unsigned int blue) : Primitive_T(GL_TRIANGLES)
{
	elementPosition.pos_width = pos_x;
	elementPosition.pos_height = pos_y;
	elementPosition.pos_length = pos_z;

	this->width = width;
	this->height = height;
	this->length = length;

	this->red = static_cast<float> (red) / 255.0f;
	this->green = static_cast<float> (green) / 255.0f;
	this->blue = static_cast<float> (blue) / 255.0f;

	InitializeVertexData();
}

void GUIObjects::Element_T::Initialize()
{
	Primitive_T::Initialize();

	glGenBuffers(1, &contour_elementArrayBuffer);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, contour_elementArrayBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, contour_elementBuffer.size() * sizeof(unsigned int),
		contour_elementBuffer.data(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GUIObjects::Element_T::Draw()
{
	//Primitive_T::Draw();
	BindBuffers();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, contour_elementArrayBuffer);
	glLineWidth(2.0f);
	glDrawElements(GL_LINES, contour_elementBuffer.size(), GL_UNSIGNED_INT, 0);
	glLineWidth(0.05f);
}

void GUIObjects::Element_T::SetColor(int red, int green, int blue)
{
	this->red = static_cast<float> (red) / 255.0f;
	this->green = static_cast<float> (green) / 255.0f;
	this->blue = static_cast<float> (blue) / 255.0f;

	InitializeVertexData();
}

void GUIObjects::Element_T::InitializeVertexData()
{
	vertexData =
	{
		// bottom
		elementPosition.pos_width, elementPosition.pos_height, elementPosition.pos_length, red, green, blue,	// 0
		elementPosition.pos_width, elementPosition.pos_height, elementPosition.pos_length + length, red, green, blue,	// 1
		elementPosition.pos_width + width, elementPosition.pos_height, elementPosition.pos_length + length, red, green, blue,	// 2
		elementPosition.pos_width + width, elementPosition.pos_height, elementPosition.pos_length, red, green, blue,	// 3

		// up
		elementPosition.pos_width, elementPosition.pos_height + height, elementPosition.pos_length, red, green, blue,	// 4
		elementPosition.pos_width, elementPosition.pos_height + height, elementPosition.pos_length + length, red, green, blue,	// 5
		elementPosition.pos_width + width, elementPosition.pos_height + height, elementPosition.pos_length + length, red, green, blue,	// 6
		elementPosition.pos_width + width, elementPosition.pos_height + height, elementPosition.pos_length, red, green, blue	// 7
	};
	
	elementBuffer =
	{
		// bottom
		0, 1, 2,
		2, 3, 0,

		3, 0, 4,
		4, 7, 3,

		0, 1, 4,
		4, 1, 5,

		1, 2, 6,
		6, 5, 2,

		2, 3, 7,
		7, 6, 3,

		4, 5, 6,
		6, 7, 4
	};

	contour_elementBuffer =
	{
		0, 1,
		0, 4,

		1, 2,
		1, 5,
		
		2, 3,
		2, 6,

		3, 0,
		3, 7,

		4, 5,
		5, 6,
		6, 7,
		7, 4
	};

}
