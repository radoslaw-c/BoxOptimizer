#include "Solver.h"
#include <iostream>

Solver_T::Solver_T()
{
	SolutionList.reserve(1000);
}

void Solver_T::InitializeElementsManually()
{
	ElementList.push_back(Element_T(100, 500, 10, 1));
	ElementList.push_back(Element_T(100, 250, 10, 2));
	ElementList.push_back(Element_T(100, 250, 10, 3));
	//ElementList.push_back(Element_T(5, 5, 1, 4));
	//ElementList.push_back(Element_T(5, 5, 1, 5));
	//ElementList.push_back(Element_T(5, 5, 1, 6));
	//ElementList.push_back(Element_T(5, 5, 1, 7));
	//ElementList.push_back(Element_T(5, 5, 1, 8));
	//ElementList.push_back(Element_T(5, 5, 1, 9));
	//ElementList.push_back(Element_T(5, 5, 1, 10));
	//ElementList.push_back(Element_T(5, 5, 1, 11));
	//ElementList.push_back(Element_T(5, 5, 1, 12));
	//ElementList.push_back(Element_T(5, 5, 1, 13));
	//ElementList.push_back(Element_T(5, 5, 1, 14));
	//ElementList.push_back(Element_T(5, 5, 1, 15));
	//ElementList.push_back(Element_T(5, 5, 1, 16));
	//ElementList.push_back(Element_T(5, 5, 1, 17));
	//ElementList.push_back(Element_T(5, 5, 1, 18));
	numberOfElements = 3;

	CalculateTotalElementArea();
}

void Solver_T::LoadElementData(const DataFrame_T& data)
{
	ElementList.resize(2 * data.ElementsCount());
	numberOfElements = data.ElementsCount();
	int elementID = 0;

	for (unsigned int it = 0; it < data.ElementsCount(); ++it)
	{
		ElementList[it] = Element_T
		(
			data.Width(it),
			data.Length(it),
			data.Height(it),
			elementID++
		);
	}
}

Solution_T Solver_T::Solve()
{
	FindSolutions();

	Solution_T* bestSolution = &SolutionList.front();
	
	for (int i = 0; i < SolutionList.size(); i++)
	{
		if (SolutionList[i].IsValid() &&
			SolutionList[i].getOutlineArea() <= bestSolution->getOutlineArea())
		{
			bestSolution = &SolutionList[i];
		}
	}
	
	return *bestSolution;
}

void Solver_T::CalculateTotalElementArea()
{
	//TODO provide a way to handle non-rectangles
	for (auto Element : ElementList)
	{
		float singleElementArea = 0;
		singleElementArea += 2 * Element.getLength() * Element.getWidth() +
			2 * Element.getLength() * Element.getHeight() +
			2 * Element.getWidth() * Element.getHeight();

		totalElementArea += singleElementArea;
	}
}
