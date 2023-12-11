#include "CalculateOutlineArea.h"

float CalculateOutlineArea(const Node_T* Node)
{
	float maxWidth = 0, maxLength = 0, maxHeight = 0;

	while (Node != NULL)
	{
		Element_T Element = Node->Element;

		if (Node->Position.pos_width + Element.getWidth() > maxWidth)
			maxWidth = Node->Position.pos_width + Element.getWidth();

		if (Node->Position.pos_length + Element.getLength() > maxLength)
			maxLength = Node->Position.pos_length + Element.getLength();

		if (Node->Position.pos_height + Element.getHeight() > maxHeight)
			maxHeight = Node->Position.pos_height + Element.getHeight();

		Node = Node->ParentNode;
	}

	float totalArea = 2 * maxHeight * maxLength + 2 * maxHeight * maxWidth +
		2 * maxWidth * maxLength;

	return totalArea;
}

BoxDimmensions CalculateBoxDimmensions(const Node_T* Node)
{
	float maxWidth = 0, maxLength = 0, maxHeight = 0;

	while (Node != NULL)
	{
		Element_T Element = Node->Element;

		if (Node->Position.pos_width + Element.getWidth() > maxWidth)
			maxWidth = Node->Position.pos_width + Element.getWidth();

		if (Node->Position.pos_length + Element.getLength() > maxLength)
			maxLength = Node->Position.pos_length + Element.getLength();

		if (Node->Position.pos_height + Element.getHeight() > maxHeight)
			maxHeight = Node->Position.pos_height + Element.getHeight();

		Node = Node->ParentNode;
	}

	return BoxDimmensions(maxWidth, maxLength, maxHeight);
}


