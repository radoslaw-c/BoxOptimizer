#include "Solver.h"

void Solver_T::Solve()
{
	FindSolutions();
	//find solution with lowest area
}

void Solver_T::FindSolutions()
{
	InitializeSolutionTree();

	//this boilds first layer of children, adds ALL remaining elements as children to the root
	for (int i = 1; i < numberOfElements; i++)
	{
		PopulateSolutionTree(ElementList[i], RootNode);
	}

	////for every child add child nodes
	//for (auto CurrentNode : RootNode.ChildNodes)
	//{
	//	for (Element_T Element : ElementList)
	//	{
	//		if (CurrentNode.Element.getId() != Element.getId() && Element.getId() != 1)
	//		{
	//			//then add this element as a child to the ChildNode
	//			//nie przetestowane, idê pisaæ znajdowanie slotów
	//			PopulateSolutionTree(Element, CurrentNode);
	//		}
	//	}
	//}
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
	//for (auto slot : availableSlots)
	for (int i = 0; i < availableSlots.size(); i++)
	{
		Position_T slot = availableSlots[i];
		Element.setPosition(slot);

		Node_T nodeToInsert = Node_T(Element, &currentNode);
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
	}
}