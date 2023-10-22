#pragma once
#include "Calibrations_T.h"
#include "Solution_T.h"
#include "ConsoleVisualiser_T.h"
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
	void InitializeSolutionTree();
	void PopulateSolutionTree(Node_T& currentNode);
	void CalculateTotalElementArea();
	void AppendToNodeMap(const Node_T* node);

	std::vector<Element_T> ElementList;
	SolutionList_T SolutionList;
	int numberOfElements = 0;
	int solutionID = 0;
	float totalElementArea = 0;
	bool jackpotHit = false;

	Calibrations_T calib;
	std::vector<std::vector<const Node_T*>> NodeMap;

	Node_T RootNode;
};

