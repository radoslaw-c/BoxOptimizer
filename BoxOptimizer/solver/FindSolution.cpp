#include "Solver.h"

static bool isPartOfSolution(const Element_T& Element, const Node_T* currentNode);

void Solver_T::FindSolutions()
{
	InitializeSolutionTree();

	PopulateSolutionTree();
}

void Solver_T::InitializeSolutionTree()
{
	Position_T RootPos = Position_T(0, 0);
	RootNode = Node_T(ElementList.front(), NULL, RootPos, calib);
	//ElementList.erase(ElementList.begin());

	//NodeMap[0].reserve(1);
	NodeMap[0].push_back(&RootNode);
}

void Solver_T::PopulateSolutionTree()
{
	for (auto it = 0; it < NodeMap.size(); it++)
	{
		auto TreeLayer = NodeMap[it];
		AllocateNextTreeLayerMem(it, TreeLayer);

		for (auto currentNode : TreeLayer)
		{
			int numberOfPossibleChildren = currentNode->availableSlots.size() * (numberOfElements - it - 1);
			if (currentNode->ChildNodes.capacity() < numberOfPossibleChildren)
			{
				//this is more than necessery
				//possible way to optimize memory usage
				currentNode->ChildNodes.reserve(numberOfPossibleChildren);
			}

			for (auto slot : currentNode->availableSlots)
			{
				for (auto element : ElementList)
				{
					if (isPartOfSolution(element, currentNode))
						continue;

					Node_T nodeToInsert = Node_T(element, currentNode, slot, calib);

					if (nodeToInsert.isValid(NodeMap, totalElementArea))
					{
						currentNode->ChildNodes.push_back(nodeToInsert);
						AppendToNodeMap(it + 1, &currentNode->ChildNodes.back());

						if (nodeToInsert.TreeLevel == numberOfElements)
						{
							Node_T* lastNode = &currentNode->ChildNodes.back();
							Solution_T solutionToInsert = Solution_T(lastNode, solutionID++);
							SolutionList.push_back(solutionToInsert);
						}
					}
				}
			}
		}
	}
}

void Solver_T::AppendToNodeMap(int treeLevel, Node_T* node)
{
	NodeMap[treeLevel].push_back(node);
}

void Solver_T::AllocateNextTreeLayerMem(int currentLayer, const std::vector<Node_T*>& TreeLayer)
{
	int totalChildren = 0;
	for (auto node : TreeLayer)
		totalChildren += node->availableSlots.size() * (ElementList.size() - currentLayer - 1);

	if (currentLayer + 1 < NodeMap.size())
		NodeMap[currentLayer + 1].reserve(totalChildren);

	//allocate memory for solution list
	if (currentLayer + 1 == NodeMap.size() - 1)
		SolutionList.reserve(totalChildren);
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
