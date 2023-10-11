#pragma once
#include "Node_T.h"

class Solution_T
{
public:
	Solution_T(Node_T* Node);
	Node_T* SolutionNode;

private:
	void Classify();
};

