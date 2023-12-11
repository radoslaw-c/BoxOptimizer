#pragma once
#include "Primitive_T.h"
#include "Position.h"

namespace GUIObjects
{
	class Element_T : public Primitive_T
	{
	public:
		Element_T(const float pos_x, const float pos_y, 
			const float pos_z);

	private:
		void InitializeVertexData();

		// fields
		Position_T elementPosition = { 0, 0, 0 };
		float width = .560, length = .720, height = .018;	//x, z, y

		glm::vec3 color_red = glm::vec3(1.0f, 0.0f, 0.0f);
	};

}