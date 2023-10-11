#include "Solver.h"

void Solver_T::Solve()
{
	FindSolutions();
	//find solution with lowest area
}

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
		if (NodeValid(nodeToInsert))
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