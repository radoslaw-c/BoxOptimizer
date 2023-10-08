#include "Element.h"
#include <vector>
#include <iostream>

class Solver_T
{
public:
	Solver_T();
	void InitializeElementsManually();

	void Solve(); // :)

private:
	void FindSolutions();

	Element_T* ElementList;


	std::vector<float*> possiblePlacements;

	int numberOfElements;

};

