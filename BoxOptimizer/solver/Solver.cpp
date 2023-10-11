#include "Solver.h"
#include <iostream>

Solver_T::Solver_T()
{
	SolutionList.reserve(1000);
}

void Solver_T::InitializeElementsManually()
{
	ElementList.push_back(Element_T(5, 11, 1));
	ElementList.push_back(Element_T(5, 3, 2));
	ElementList.push_back(Element_T(6, 2, 3));
	ElementList.push_back(Element_T(7, 3, 4));
	numberOfElements = 4;

	CalculateTotalElementArea();
}

void Solver_T::Solve()
{
	FindSolutions();
	//find solution with lowest area


}

