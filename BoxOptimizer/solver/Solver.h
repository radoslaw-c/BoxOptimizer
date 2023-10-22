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
	void PopulateSolutionTree();
	void CalculateTotalElementArea();
	void AppendToNodeMap(int treeLevel, Node_T* node);
	void AllocateNextTreeLayerMem(int currentLayer, const std::vector<Node_T*>& TreeLayer);

	std::vector<Element_T> ElementList;
	SolutionList_T SolutionList;
	int numberOfElements = 0;
	int solutionID = 0;
	float totalElementArea = 0;

	Calibrations_T calib;
	std::vector<std::vector<Node_T*>> NodeMap;

	Node_T RootNode;
};

