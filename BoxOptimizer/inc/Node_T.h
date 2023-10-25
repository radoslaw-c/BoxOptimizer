#pragma once
#include "Element.h"
#include "Calibrations_T.h"
#include <vector>
#include <algorithm>
#include <map>

#define NODE_MAP_T std::vector<std::vector<Node_T*>>
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
	bool isValid(NODE_MAP_T NodeMap, float totalElementArea) const;

	bool CheckJackpot(const int numberOfElements, const float totalElementArea) const;

	Element_T Element;
	float OutlineArea = 0;
	Node_T* ParentNode = NULL;
	std::vector<Node_T> ChildNodes;
	SlotList availableSlots;
	int TreeLevel = 1;
	Position_T Position;
	std::map<int, Position_T> elementMap;
	bool isJackpot = false;

private:
	void FindAvailableSlots();
	void UpdateElementMap();
	bool checkNodeExists(NODE_MAP_T NodeMap) const;
	inline bool checkAreaValid(float totalElementArea) const;
};

typedef NODE_MAP_T NodeMap_T;
