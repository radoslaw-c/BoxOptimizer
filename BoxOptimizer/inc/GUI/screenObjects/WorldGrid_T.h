#pragma once
#include "Primitive_T.h"

class WorldGrid_T : public Primitive_T
{
public:
	WorldGrid_T();
private:
	// methods
	void InitializeVertexData();

	// fields
	int numberOfVerts = 100;
	int maxDist = 20; //dist range <-20; 20>
};
