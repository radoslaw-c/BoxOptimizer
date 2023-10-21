#include "Solver.h"
#include <iostream>

Solver_T::Solver_T()
{
	SolutionList.reserve(1000);
}

void Solver_T::InitializeElementsManually()
{
	ElementList.push_back(Element_T(5, 5, 1));
	ElementList.push_back(Element_T(5, 5, 2));
	ElementList.push_back(Element_T(5, 5, 3));
	ElementList.push_back(Element_T(5, 5, 4));
	ElementList.push_back(Element_T(5, 5, 5));
	ElementList.push_back(Element_T(5, 5, 6));
	numberOfElements = 6;

	NodeMap.resize(numberOfElements);

	//CalculateTotalElementArea();
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

