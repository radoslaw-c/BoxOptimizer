#pragma once
#include "Primitive_T.h"
#include "Position.h"

namespace GUIObjects
{
	//class ElementCountour

	class Element_T : public Primitive_T
	{
	public:
		Element_T(float pos_x, float pos_y, float pos_z,
			float width, float height, float length,
			unsigned int red = 255, unsigned int green = 0, unsigned int blue = 0);
		
		void Initialize();
		void Draw();


		// setters
		void SetColor(int red, int green, int blue);

	private:
		void InitializeVertexData();

		// fields
		Position_T elementPosition = { 0, 0, 0 };
		float width = 0.0f, length = 0.0f, height = 0.0f;	//x, z, y
		float red = 0, green = 0, blue = 0;

		unsigned int contour_elementArrayBuffer = 0;
		std::vector<unsigned int> contour_elementBuffer;
	};
}