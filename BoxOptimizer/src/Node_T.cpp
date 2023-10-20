#include "Node_T.h"

static bool positionExists(const SlotList& parentSlots, const Position_T& position);

Node_T::Node_T(Element_T Element, Node_T* ParentNode, Position_T Position)
{
	this->Element = Element;
	this->ParentNode = ParentNode;
	TreeLevel = ParentNode == NULL ? 1 : ParentNode->TreeLevel + 1;
	this->Position = Position;

	FindAvailableSlots();
}

void Node_T::FindAvailableSlots()
{
	SlotList PartentSlots;
	if (ParentNode != NULL)
		PartentSlots = ParentNode->availableSlots;

	Position_T availableSlot1;
	availableSlot1.pos_width = Element.getWidth() + Position.pos_width;
	availableSlot1.pos_length = Position.pos_length;
	if (!positionExists(PartentSlots, availableSlot1))
		availableSlots.push_back(availableSlot1);

	Position_T availableSlot2;
	availableSlot2.pos_width = Position.pos_width;
	availableSlot2.pos_length = Element.getLength() + Position.pos_length;
	if (!positionExists(PartentSlots, availableSlot2))
		availableSlots.push_back(availableSlot2);
}

static bool positionExists(const SlotList& parentSlots, const Position_T& position)
{
	for (auto parentSlot : parentSlots)
	{
		if (parentSlot == position)
			return true;
	}
	return false;
}