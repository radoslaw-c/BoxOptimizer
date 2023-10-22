#include "Solver.h"

static bool isPartOfSolution(const Element_T& Element, const Node_T* currentNode);

void Solver_T::FindSolutions()
{
	InitializeSolutionTree();

	PopulateSolutionTree(RootNode);
}

void Solver_T::InitializeSolutionTree()
{
	Position_T RootPos = Position_T(0, 0);
	RootNode = Node_T(ElementList.front(), NULL, RootPos);
	ElementList.erase(ElementList.begin());

	AppendToNodeMap(&RootNode);
}

void Solver_T::PopulateSolutionTree(Node_T& currentNode)
{
	//preallocate memory for children
	int numberOfPossibleChildren = currentNode.availableSlots.size() * numberOfElements;
	if (currentNode.ChildNodes.capacity() < numberOfPossibleChildren)
	{
		//this is more than necessery
		//possible way to optimize memory usage
		currentNode.ChildNodes.reserve(numberOfPossibleChildren);
	}

	//loop through available slots
	for (auto slot : currentNode.availableSlots)
	{
		for (auto element : ElementList)
		{
			if (isPartOfSolution(element, &currentNode))
				continue;

			Node_T nodeToInsert = Node_T(element, &currentNode, slot);

			if (nodeToInsert.isValid(NodeMap, totalElementArea))
			{
				currentNode.ChildNodes.push_back(nodeToInsert);
				AppendToNodeMap(&currentNode.ChildNodes.back());

				if (nodeToInsert.TreeLevel < numberOfElements)
					PopulateSolutionTree(currentNode.ChildNodes.back());

				if (!jackpotHit && nodeToInsert.TreeLevel == numberOfElements)
				{
					Node_T* lastNode = &currentNode.ChildNodes.back();
					Solution_T solutionToInsert = Solution_T(lastNode, solutionID++);
					SolutionList.push_back(solutionToInsert);
				}
				if (nodeToInsert.CheckJackpot(numberOfElements, totalElementArea) || jackpotHit)
				{
					jackpotHit = true;
					break;
				}
			}
		}
		if (jackpotHit)
			break;
	}
}

static bool isPartOfSolution(const Element_T& Element, const Node_T* currentNode)
{
	while (currentNode != NULL)
	{
		if (Element.getId() == currentNode->Element.getId())
			return true;
		currentNode = currentNode->ParentNode;
	}
	return false;
}
 
void Solver_T::AppendToNodeMap(const Node_T* node)
{
	NodeMap[node->TreeLevel - 1].push_back(node);
}