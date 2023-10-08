#include "Solver.h"
#include <iostream>

Solver_T::Solver_T()
{
	float initialPosition[2] = { 0, 0 };
	possiblePlacements.push_back(initialPosition);
}

void Solver_T::InitializeElementsManually()
{
	ElementList = new Element_T[2];
	ElementList[0] = Element_T(11, 5, 1);
	ElementList[1] = Element_T(5, 3, 2);

	numberOfElements = 2;
}