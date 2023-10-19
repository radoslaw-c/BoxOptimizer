#include "CalculateOutlineArea.h"

//float CalculateOutlineArea(Node_T Node)
//{
//	Element_T Element = Node.Element;
//	float maxWidth = Element.getPosition().pos_width +
//		Element.getWidth();
//	float maxLength = Element.getPosition().pos_length +
//		Element.getLength();
//
//	return maxWidth * maxLength;
//}

float CalculateOutlineArea(const Node_T* Node)
{
	float maxWidth = 0, maxLength = 0;

	while (Node != NULL)
	{
		Element_T Element = Node->Element;

		if (Element.getPosition().pos_width + Element.getWidth() > maxWidth)
			maxWidth = Element.getPosition().pos_width + Element.getWidth();

		if (Element.getPosition().pos_length + Element.getLength() > maxLength)
			maxLength = Element.getPosition().pos_length + Element.getLength();

		Node = Node->ParentNode;
	}

	return maxWidth * maxLength;
}