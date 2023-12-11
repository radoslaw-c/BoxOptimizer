#include "screenObjects/Element_T.h"

using GUIObjects::Element_T;
Element_T::Element_T(float pos_x, float pos_y, float pos_z,
	float width, float height, float length) : Primitive_T(GL_TRIANGLES)
{
	elementPosition.pos_width = pos_x;
	elementPosition.pos_height = pos_y;
	elementPosition.pos_length = pos_z;

	this->width = width;
	this->height = height;
	this->length = length;

	InitializeVertexData();
}

void GUIObjects::Element_T::InitializeVertexData()
{
	vertexData =
	{
		// bottom
		elementPosition.pos_width, elementPosition.pos_height, elementPosition.pos_length, 1.0f, 0.0f, 0.0f,	// 0
		elementPosition.pos_width, elementPosition.pos_height, elementPosition.pos_length + length, 1.0f, 0.0f, 0.0f,	// 1
		elementPosition.pos_width + width, elementPosition.pos_height, elementPosition.pos_length + length, 1.0f, 0.0f, 0.0f,	// 2
		elementPosition.pos_width + width, elementPosition.pos_height, elementPosition.pos_length, 1.0f, 0.0f, 0.0f,	// 3

		// up
		elementPosition.pos_width, elementPosition.pos_height + height, elementPosition.pos_length, 1.0f, 0.0f, 0.0f,	// 4
		elementPosition.pos_width, elementPosition.pos_height + height, elementPosition.pos_length + length, 1.0f, 0.0f, 0.0f,	// 5
		elementPosition.pos_width + width, elementPosition.pos_height + height, elementPosition.pos_length + length, 1.0f, 0.0f, 0.0f,	// 6
		elementPosition.pos_width + width, elementPosition.pos_height + height, elementPosition.pos_length, 1.0f, 0.0f, 0.0f	// 7
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

}
