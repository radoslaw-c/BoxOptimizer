#include "screenObjects/Element_T.h"

using GUIObjects::Element_T;
Element_T::Element_T() : Primitive_T(GL_TRIANGLES)
{
	InitializeVertexData();
}

void GUIObjects::Element_T::InitializeVertexData()
{
	vertexData =
	{
		elementPosition.pos_width, elementPosition.pos_length, elementPosition.pos_height, 1.0f, 0.0f, 0.0f, // 0
		elementPosition.pos_width + width, elementPosition.pos_length, elementPosition.pos_height, 1.0f, 0.0f, 0.0f, // 1
		elementPosition.pos_width, elementPosition.pos_length + length, elementPosition.pos_height, 1.0f, 0.0f, 0.0f, // 2
	};

	elementBuffer =
	{
		0, 1, 2
	};
}
