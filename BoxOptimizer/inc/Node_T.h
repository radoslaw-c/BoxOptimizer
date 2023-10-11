#pragma once
#include "Element.h"
#include <vector>

class Node_T
{
public:
	Node_T() {};
	//and that's a copy -- a way to optimize memory usage by passing a reference instead of value
	Node_T(Element_T Element)
	{
		this->Element = Element;
	}

	Node_T(Element_T Element, Node_T* ParentNode)
	{
		this->Element = Element;
		this->ParentNode = ParentNode;
		TreeHierarchy += ParentNode->TreeHierarchy;
	}
	Element_T Element;
	Node_T* ParentNode = nullptr;
	std::vector<Node_T> ChildNodes;
	int TreeHierarchy = 1;
};
