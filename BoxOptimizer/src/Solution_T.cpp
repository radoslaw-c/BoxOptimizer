#include "Solution_T.h"

Solution_T::Solution_T(Node_T* Node)
{
	SolutionNode = Node;
	Classify();
}

Solution_T::Solution_T(Node_T* Node, int id)
{
	SolutionNode = Node;
	this->id = id;
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