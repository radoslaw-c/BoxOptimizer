#include "Solution_T.h"

Solution_T::Solution_T(Node_T* Node)
{
	SolutionNode = Node;
	Classify();
}

void Solution_T::Classify()
{
	outlineArea = CalculateOutlineArea(SolutionNode);
	LayerValidity();



}

void Solution_T::LayerValidity()
{
	//coming soon
}