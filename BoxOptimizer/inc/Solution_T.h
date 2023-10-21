#pragma once
#include "Node_T.h"
#include "CalculateOutlineArea.h"
#include <limits>

class Solution_T
{
public:
	Solution_T(Node_T* Node);
	Solution_T(Node_T* Node, int id);
	Solution_T() {};
	Node_T* SolutionNode;
	int id = -1;
	float getOutlineArea() { return outlineArea; }

private:
	void Classify();

	void LayerValidity();
	float outlineArea = std::numeric_limits<float>::max();
};

typedef std::vector<Solution_T> SolutionList_T;