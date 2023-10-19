#include "Solver.h"

void Solver_T::FindSolutions()
{
	InitializeSolutionTree();

	for (int i = 1; i < numberOfElements; i++)
	{
		PopulateSolutionTree(ElementList[i], RootNode);
	}
}

void Solver_T::InitializeSolutionTree()
{
	Position_T initialPosition = Position_T(0, 0);
	RootNode = Node_T(ElementList[0]); //REMARK does not change values of original elements

	//initialize position
	RootNode.Element.setPosition(initialPosition);
}

void Solver_T::PopulateSolutionTree(Element_T Element, Node_T& currentNode)
{
	auto availableSlots = FindAvailableSlots(currentNode);
	int numberOfPossibleChildren = availableSlots.size() * numberOfElements;

	if (currentNode.ChildNodes.capacity() < numberOfPossibleChildren)
	{
		//this is more than necessery
		//possible way to optimize memory usage
		currentNode.ChildNodes.reserve(numberOfPossibleChildren);
	}

	for (int i = 0; i < availableSlots.size(); i++)
	{
		Position_T slot = availableSlots[i];
		Element.setPosition(slot);

		Node_T nodeToInsert = Node_T(Element, &currentNode);
		if (NodeValid(&nodeToInsert))
		{
			currentNode.ChildNodes.push_back(nodeToInsert);
			while (!IsLastNode(nodeToInsert))
			{
				Node_T& head = currentNode.ChildNodes.back();

				for (const auto& ElementToInsert : ElementList)
				{
					if (!IsAncestor(ElementToInsert, head))
					{
						PopulateSolutionTree(ElementToInsert, head);
					}
				}
				break;
			}

			auto solution = currentNode.ChildNodes.back();
			if (IsLastNode(solution))
				SolutionList.push_back(&currentNode.ChildNodes.back());
		}
	}
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

		if (availableSlot1 != positionOfChildNode)
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

/*
* This function is supposed to contain conditions to check if
* the node is about to be inserted makes entire config good enough.
*
* Conditons:
* 1. Outline area can't be greater than 2x total area of individual elements.
*
*/

bool Solver_T::NodeValid(const Node_T* Node)
{
	bool areaValid = CalculateOutlineArea(Node) <= totalElementArea * calib.maxAllowedArea;

	return areaValid && true;
}