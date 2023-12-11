#include "screenObjects\WorldGrid_T.h"

WorldGrid_T::WorldGrid_T() : Primitive_T(GL_LINES)
{
	// it first calls constructor of the partent class
	// in this case construnctor of Primitive_T

	InitializeVertexData();
}

void WorldGrid_T::InitializeVertexData()
{
	vertexData.resize(numberOfVerts * numberOfVerts * 6);
	elementBuffer.resize(numberOfVerts * (numberOfVerts - 1) * 4);

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
			vertexData[vertexStrartIndex + 0] = x;
			vertexData[vertexStrartIndex + 1] = y;
			vertexData[vertexStrartIndex + 2] = z;
			vertexData[vertexStrartIndex + 3] = r;
			vertexData[vertexStrartIndex + 4] = g;
			vertexData[vertexStrartIndex + 5] = b;
		}
	}

	std::size_t lineEndpointIdx = 0;
	
	for (std::size_t row = 0; row < numberOfVerts; ++row)
	{
		for (std::size_t column = 0; column < numberOfVerts - 1; ++column)
		{
			elementBuffer[lineEndpointIdx++] = row * numberOfVerts + column;
			elementBuffer[lineEndpointIdx++] = row * numberOfVerts + column + 1;
		}
	}

	for (std::size_t row = 0; row < numberOfVerts - 1; ++row)
	{
		for (std::size_t column = 0; column < numberOfVerts; ++column)
		{
			elementBuffer[lineEndpointIdx++] = row * numberOfVerts + column;
			elementBuffer[lineEndpointIdx++] = (row + 1) * numberOfVerts + column;
		}
	}


}
