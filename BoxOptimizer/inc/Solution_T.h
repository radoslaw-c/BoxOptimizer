#pragma once
#include "Node_T.h"
#include "CalculateOutlineArea.h"
#include <limits>

class Outline_T
{
public:

};

class Solution_T
{
public:
	Solution_T(Node_T* Node);
	Solution_T() {};
	Node_T* SolutionNode;

	float getOutlineArea() { return outlineArea; }

private:
	void Classify();

	void LayerValidity();
	float outlineArea = std::numeric_limits<float>::max();
};

