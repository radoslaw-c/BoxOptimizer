#include "Solver.h"
#include <iostream>


void Solver_T::InitializeElementsManually()
{
	ElementList.push_back(Element_T(5, 11, 1));
	ElementList.push_back(Element_T(5, 3, 2));
	ElementList.push_back(Element_T(6, 2, 3));
	ElementList.push_back(Element_T(7, 3, 4));
	numberOfElements = 4;

	CalculateTotalElementArea();
}

/*
* REMARKS::
* 1. Works good for single-node scenario, others were NOT tested!
*/

std::vector<Position_T> Solver_T::FindAvailableSlots(Node_T currentNode)
{	
	std::vector<Position_T> availableSlots;
	Position_T positionOfChildNode;

	while (true)
	{
		Position_T availableSlot1;
		availableSlot1.pos_width = currentNode.Element.getWidth() + 
			currentNode.Element.getPosition().pos_width;
		availableSlot1.pos_length = currentNode.Element.getPosition().pos_length;
		
		if ( availableSlot1 != positionOfChildNode)
		{
			availableSlots.push_back(availableSlot1);
		}

		Position_T availableSlot2;
		availableSlot2.pos_width = currentNode.Element.getPosition().pos_width;
		availableSlot2.pos_length = currentNode.Element.getLength() + 
			currentNode.Element.getPosition().pos_length;

		if (availableSlot2 != positionOfChildNode)
		{
			availableSlots.push_back(availableSlot2);
		}
		
		positionOfChildNode = currentNode.Element.getPosition();

		if (currentNode.ParentNode != NULL)
			currentNode = *currentNode.ParentNode;
		else
			break;
	}

	return availableSlots;
}

//
// REMARKS::
// 1. returns the node as ancestor of itself 
//

std::vector<Element_T> Solver_T::GetAncestors(Node_T node)
{
	std::vector<Element_T> ancestors;

	while (true)
	{
		ancestors.push_back(node.Element);
		if (node.ParentNode != NULL)
			node = *node.ParentNode;
		else
			break;
	}

	return ancestors;
}

bool Solver_T::IsLastNode(Node_T Node)
{
	return Node.TreeHierarchy == numberOfElements;
}

//
// checks if  the object that is about to be inserted is already a part of a partent node of a givent node
//

bool Solver_T::IsAncestor(Element_T Element, Node_T Node)
{
	std::vector<Element_T> ancestors = GetAncestors(Node);

	for (Element_T ancestor : ancestors)
	{
		if (Element.getId() == ancestor.getId())
			return true;
	}
	return false;
}

//
// Function calculates area of all elements passed
// to the solver 
//
void Solver_T::CalculateTotalElementArea()
{
	//TODO provide a way to handle non-rectangles

	for (auto Element : ElementList)
	{
		totalElementArea += Element.getLength() * Element.getWidth();
	}
}

float Solver_T::CalculateOutlineArea(Node_T Node)
{
	Element_T Element = Node.Element;
	float maxWidth = Element.getPosition().pos_width +
		Element.getWidth();
	float maxLength = Element.getPosition().pos_length +
		Element.getLength();

	return maxWidth * maxLength;
}