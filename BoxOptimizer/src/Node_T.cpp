#include "Node_T.h"
#include "CalculateOutlineArea.h"

static bool positionValid(const Node_T* currentNode,const SlotList& parentSlots, const Position_T& position);
static bool compareNodes(const Node_T* node1, const Node_T* node2);

Node_T::Node_T(Element_T Element, Node_T* ParentNode, Position_T Position)
{
	this->Element = Element;
	this->ParentNode = ParentNode;
	TreeLevel = ParentNode == NULL ? 1 : ParentNode->TreeLevel + 1;
	this->Position = Position;

	UpdateElementMap();
	FindAvailableSlots();
	OutlineArea = CalculateOutlineArea(this);
}

void Node_T::FindAvailableSlots()
{
	SlotList PartentSlots;
	if (ParentNode != NULL)
	{
		PartentSlots = ParentNode->availableSlots;
		availableSlots = PartentSlots;
		availableSlots.erase(std::remove(availableSlots.begin(), availableSlots.end(), Position),
			availableSlots.end());
	}

	Position_T availableSlot1;
	availableSlot1.pos_width = Element.getWidth() + Position.pos_width;
	availableSlot1.pos_length = Position.pos_length;
	if (positionValid(this, PartentSlots, availableSlot1) && availableSlot1 != Position)
		availableSlots.push_back(availableSlot1);

	Position_T availableSlot2;
	availableSlot2.pos_width = Position.pos_width;
	availableSlot2.pos_length = Element.getLength() + Position.pos_length;
	if (positionValid(this, PartentSlots, availableSlot2) && availableSlot2 != Position)
		availableSlots.push_back(availableSlot2);
}

static bool positionValid(const Node_T* currentNode,const SlotList& parentSlots, const Position_T& position)
{
	for (auto parentSlot : parentSlots)
	{
		if (parentSlot == position)
			return false;
	}

	while (currentNode != NULL)
	{
		if (currentNode->Position == position)
			return false;
		
		currentNode = currentNode->ParentNode;
	}

	return true;
}

bool Node_T::isValid(NodeMap_T NodeMap, float totalElementArea) const
{
	//THE validity check function

	// 1. Check if outline area ins't too big
	if (!checkAreaValid(totalElementArea))
		return false;

	// 2. Identical branch is already a part of solution
	// disabled because performance penalty - rougly 1000 times
	
	if (checkNodeExists(NodeMap))
		return false;

	return true;
}

bool Node_T::checkNodeExists(NodeMap_T NodeMap) const
{
	std::vector<const Node_T*> ExistingNodes = NodeMap[TreeLevel - 1];

	for (auto ExistingNode : ExistingNodes)
	{
		if (compareNodes(ExistingNode, this))
			return true;
	}

	return false;
}

static bool compareNodes(const Node_T* node1, const Node_T* node2)
{
	if (node1->OutlineArea != node2->OutlineArea)
		return false;


	
	//if (node1->elementMap != node2->elementMap)
	//	return false;
	
	//return true;
	return false;
}

inline bool Node_T::checkAreaValid(float totalElementArea) const
{
	return CalculateOutlineArea(this) <= totalElementArea * 1.25;
}

void Node_T::UpdateElementMap()
{
	if (ParentNode != NULL)
		elementMap = ParentNode->elementMap;
	elementMap[Element.getId()] = Position;
}

bool Node_T::CheckJackpot(const int numberOfElements, const float totalElementArea) const
{
	if (numberOfElements == TreeLevel && OutlineArea == totalElementArea)
		return true;
	else
		return false;
}