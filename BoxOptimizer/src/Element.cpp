#include "Element.h"
#include <iostream>

Element_T::Element_T()
{
}

Element_T::Element_T(float width, float length, int id)
{
	_length = length;
	_width = width;
	_id = id;
	std::cout << "Element initialized!\n";
}

