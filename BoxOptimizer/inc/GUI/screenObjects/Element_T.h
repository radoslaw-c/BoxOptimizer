#pragma once
#include "Primitive_T.h"
#include "Position.h"

namespace GUIObjects
{
	class Element_T : public Primitive_T
	{
	public:
		Element_T();

	private:
		void InitializeVertexData();

		// fields
		Position_T elementPosition = { 0, 0, 0 };
		float width = 5.6, length = 7.20, height = 0.18;	//x, z, y
	};

}