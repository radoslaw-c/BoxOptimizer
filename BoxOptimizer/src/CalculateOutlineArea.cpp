#include "CalculateOutlineArea.h"

float CalculateOutlineArea(const Node_T* Node)
{
	float maxWidth = 0, maxLength = 0;

	while (Node != NULL)
	{
		Element_T Element = Node->Element;

		if (Node->Position.pos_width + Element.getWidth() > maxWidth)
			maxWidth = Node->Position.pos_width + Element.getWidth();

		if (Node->Position.pos_length + Element.getLength() > maxLength)
			maxLength = Node->Position.pos_length + Element.getLength();

		Node = Node->ParentNode;
	}

	return maxWidth * maxLength;
}