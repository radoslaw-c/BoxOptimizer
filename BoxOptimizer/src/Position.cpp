#include "Position.h"

Vertex_T::Vertex_T(float width, float length, int ElementID) : Position_T(width, length)
{
	this->ElementID = ElementID;
}

bool operator== (const Position_T& pos1, const Position_T& pos2)
{
	return pos1.pos_length == pos2.pos_length && pos1.pos_width == pos2.pos_width;
}

bool operator!= (const Position_T& pos1, const Position_T& pos2)
{
	return !(pos1 == pos2);
}

bool operator< (const Position_T& pos1, const Position_T& pos2)
{
	return pos1.pos_length < pos2.pos_length && pos1.pos_width < pos2.pos_width;
}

bool comparePositions(const Position_T& pos1, const Position_T& pos2)
{
	if (pos1.pos_width == pos2.pos_width)
		return pos1.pos_length < pos2.pos_length;

	return pos1.pos_width < pos2.pos_width;
}

bool comaprePositions_widthLess(const Position_T& pos1, const Position_T& pos2)
{
	return pos1.pos_width < pos2.pos_width;
}

bool comaprePositions_lengthLess(const Position_T& pos1, const Position_T& pos2)
{
	return pos1.pos_length < pos2.pos_length;
}

float positionDistance(const Position_T& pos1, const Position_T& pos2, bool use3D)
{
	if (use3D)
	{
		return std::hypot(pos1.pos_width - pos2.pos_width,
			pos1.pos_length - pos2.pos_length,
			pos1.pos_height - pos2.pos_height);
	}
	else
	{
		return std::hypot(pos1.pos_width - pos2.pos_width,
			pos1.pos_length - pos2.pos_length);
	}
}
