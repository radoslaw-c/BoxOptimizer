#pragma once
#include "Element.h"
#include <vector>

typedef std::vector<Position_T> SlotList;

class Node_T
{
public:
	Node_T() {};
	//and that's a copy -- a way to optimize memory usage by passing a reference instead of value
	Node_T(Element_T Element)
	{
		this->Element = Element;
	}

	Node_T(Element_T Element, Node_T* ParentNode, Position_T Position);

	Element_T Element;
	Node_T* ParentNode = nullptr;
	std::vector<Node_T> ChildNodes;
	SlotList availableSlots;
	int TreeLevel = 1;
	Position_T Position;

private:
	void FindAvailableSlots();
};
