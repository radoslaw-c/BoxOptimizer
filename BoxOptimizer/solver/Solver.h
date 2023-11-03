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
	void CalculateTotalElementArea();

	//all the stuff related to A* algo
	void A_starFind();
	void AppendChildrenToNode(Node_T* currentNode);
	std::vector<Node_T*> NodeQueue;

	ElementList_T ElementList;
	SolutionList_T SolutionList;
	int numberOfElements = 0;
	float totalElementArea = 0;

	Calibrations_T calib;
	int nodeID = 0;

	Node_T RootNode;
};
