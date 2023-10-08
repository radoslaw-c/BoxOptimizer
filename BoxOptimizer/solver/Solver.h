#include "Element.h"
#include <vector>
#include <iostream>

class Position_T
{
public:
	int width, length;
};

class ElementPlacement_T
{
public:
	int id;
	Position_T position;
	float width = 0;
	float length = 0;
};

class Solution_T
{
public:
	std::vector<ElementPlacement_T> placement;
	float sufraceArea = 0;
	float max_x = 0, max_y = 0;
};


class Solver_T
{
public:
	Solver_T();
	void InitializeElementsManually();

	void Solve(); // :)

private:
	void FindSolutions();
	std::vector<Solution_T> solutions;

	void FindPossiblePlacements(const Solution_T solution);
	std::vector<float*> possiblePlacements;

	Element_T* ElementList;
	int numberOfElements;

};

