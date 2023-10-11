#include "CalculateOutlineArea.h"

float CalculateOutlineArea(Node_T Node)
{
	Element_T Element = Node.Element;
	float maxWidth = Element.getPosition().pos_width +
		Element.getWidth();
	float maxLength = Element.getPosition().pos_length +
		Element.getLength();

	return maxWidth * maxLength;
}
