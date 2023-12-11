#include "screenObjects\WorldGrid_T.h"

WorldGrid_T::WorldGrid_T() : Primitive_T(GL_POINTS)
{
	// it first calls constructor of the partent class
	// in this case construnctor of Primitive_T

	InitializeVertexData();
}

void WorldGrid_T::InitializeVertexData()
{
	vertexData.resize(numberOfVerts * numberOfVerts * 6);
	elementBuffer.resize(numberOfVerts * numberOfVerts * 2);

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

	for (int idx = 0; idx < elementBuffer.size(); ++idx)
	{
		elementBuffer[idx] = idx;
	}
}
