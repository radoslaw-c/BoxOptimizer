#pragma once
#include "Node_T.h"
#include "CalculateOutlineArea.h"

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

private:
	void Classify();

	void LayerValidity();
	float outlineArea = 0;
};

