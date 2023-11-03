#include "Solver.h"

static bool isPartOfSolution(const Element_T& Element, const Node_T* currentNode);
static float calculateRemainingArea(const Node_T& Node, const ElementList_T& ElementList);

void Solver_T::FindSolutions()
{
	InitializeSolutionTree();

	A_starFind();
}

void Solver_T::InitializeSolutionTree()
{
	Position_T RootPos = Position_T(0, 0);
	RootNode = Node_T(ElementList.front(), NULL, RootPos, 0, calib);
	RootNode.RemainingArea(totalElementArea);
	
	RootNode.ChildNodes.reserve(RootNode.availableSlots.size() *
		(numberOfElements - 1));

	NodeQueue.reserve(1000);
	NodeQueue.push_back(&RootNode);
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

static float calculateRemainingArea(const Node_T& Node, const ElementList_T& ElementList)
{
	float remainingArea = 0;
	for (const auto& Element : ElementList)
	{
		if (!isPartOfSolution(Element, &Node))
		{
			float singleElementArea = 0;
			singleElementArea += 2 * Element.getLength() * Element.getWidth() +
				2 * Element.getLength() * Element.getHeight() +
				2 * Element.getWidth() * Element.getHeight();
			
			remainingArea += singleElementArea;
		}
	}
	return remainingArea;
}

void Solver_T::A_starFind()
{
	while (true)
	{
		Node_T* currentNode = NodeQueue.front();
		AppendChildrenToNode(currentNode);
		NodeQueue.erase(NodeQueue.begin());

		std::sort(NodeQueue.begin(), NodeQueue.end(), CompareNodes_TotalSolutionArea);

		if (NodeQueue.front()->TreeLevel == numberOfElements)
		{
			Solution_T tempSolution = NodeQueue.front();
			if (tempSolution.IsValid())
			{
				SolutionList.push_back(tempSolution);
				break;
			}
			else
			{
				NodeQueue.erase(NodeQueue.begin());
			}
		}
	}
}

void Solver_T::AppendChildrenToNode(Node_T* currentNode)
{
	for (const auto& slot : currentNode->availableSlots)
	{
		for (const auto& element : ElementList)
		{
			if (isPartOfSolution(element, currentNode))
				continue;
	
			Node_T nodeToInsert = Node_T(element, currentNode, slot, ++nodeID, calib);
	
			if (nodeToInsert.isValid(totalElementArea))
			{
				auto remainingArea = calculateRemainingArea(nodeToInsert, ElementList);
				nodeToInsert.RemainingArea(remainingArea);
	
				currentNode->ChildNodes.push_back(nodeToInsert);
				int numberOfPossibleChildren = nodeToInsert.availableSlots.size() *
					(numberOfElements - nodeToInsert.TreeLevel);
				auto& lastNode = currentNode->ChildNodes.back();
				lastNode.ChildNodes.reserve(numberOfPossibleChildren);

				NodeQueue.push_back(&currentNode->ChildNodes.back());
			}
		}
	}
}