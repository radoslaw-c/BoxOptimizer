#include "Solver.h"
#include <iostream>

Solver_T::Solver_T()
{
	SolutionList.reserve(1000);
}

void Solver_T::InitializeElementsManually()
{
	ElementList.push_back(Element_T(10,3, 1));
	ElementList.push_back(Element_T(5, 2, 2));
	ElementList.push_back(Element_T(5, 5, 3));
	ElementList.push_back(Element_T(5, 5, 4));
	ElementList.push_back(Element_T(5, 5, 5));
	ElementList.push_back(Element_T(5, 5, 6));
	ElementList.push_back(Element_T(5, 5, 7));
	//ElementList.push_back(Element_T(5, 5, 8));
	//ElementList.push_back(Element_T(5, 2, 9));
	//ElementList.push_back(Element_T(5, 5, 10));
	//ElementList.push_back(Element_T(5, 5, 11));
	//ElementList.push_back(Element_T(5, 5, 12));
	//ElementList.push_back(Element_T(5, 5, 13));
	//ElementList.push_back(Element_T(5, 5, 14));
	//ElementList.push_back(Element_T(5, 5, 15));
	//ElementList.push_back(Element_T(5, 5, 16));
	//ElementList.push_back(Element_T(5, 5, 17));
	//ElementList.push_back(Element_T(5, 5, 18));
	numberOfElements = 7;

	NodeMap.resize(numberOfElements);
	CalculateTotalElementArea();
}

void Solver_T::Solve()
{
	FindSolutions();
	//find solution with lowest area

	Solution_T* bestSolution = &SolutionList.front();

	for (int i = 0; i < SolutionList.size(); i++)
	{
		if (SolutionList[i].getOutlineArea() < bestSolution->getOutlineArea())
			bestSolution = &SolutionList[i];
	}

	ConsoleVisualiser_T consolePrint(*bestSolution);
	consolePrint.DrawSolution();
	consolePrint.PrintSolutionDetails();

	//for (int i = 0; i < SolutionList.size(); i++)
	//{
	//	ConsoleVisualiser_T consolePrint(SolutionList[i]);
	//	consolePrint.DrawSolution();
	//	consolePrint.PrintSolutionDetails();
	//}
}

void Solver_T::CalculateTotalElementArea()
{
	//TODO provide a way to handle non-rectangles
	for (auto Element : ElementList)
	{
		totalElementArea += Element.getLength() * Element.getWidth();
	}
}

