#include "Element.h"
#include <iostream>

Element::Element()
{
}

Element::Element(float length, float width)
{
	_length = length;
	_width = width;
	std::cout << "Element initialized!\n";
}

