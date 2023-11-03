#pragma once
#include "Element.h"
#include "Calibrations_T.h"
#include <vector>
#include <algorithm>

typedef std::vector<Position_T> SlotList;

class Node_T
{
public:
	Node_T() {};
	//and that's a copy -- a way to optimize memory usage by passing a reference instead of value
	Node_T(const Element_T& Element)
	{
		this->Element = Element;
	}

	//Node_T(Element_T Element, Node_T* ParentNode, Position_T Position);
	Node_T(Element_T Element, Node_T* ParentNode, Position_T Position, int id, const Calibrations_T &calib);
	bool isValid(float totalElementArea) const;

	Element_T Element;
	float OutlineArea = 0;
	Node_T* ParentNode = NULL;
	std::vector<Node_T> ChildNodes;
	SlotList availableSlots;
	int TreeLevel = 1;
	Position_T Position;
	short layer = -1;
	bool isJackpot = false;

	void RemainingArea(float remainingArea);

	//getters
	float TotalSolutionArea() const { return totalSolutionArea; };
	//setters

private:
	void GetNodeLayer(const Calibrations_T& calib);
	void FindAvailableSlots();
	inline bool checkAreaValid(float totalElementArea) const;	
	int id = 0;
	float remainingArea = 0;
	float totalSolutionArea = 0;	//for rating purposes for A* algorithm
};

bool CompareNodes_TotalSolutionArea(const Node_T* node1, const Node_T* node2);
