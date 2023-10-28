#include "Position.h"

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

bool ComparePositions(const Position_T& pos1, const Position_T& pos2)
{
	if (pos1.pos_width == pos2.pos_width)
		return pos1.pos_length < pos2.pos_length;

	return pos1.pos_width < pos2.pos_width;
}
