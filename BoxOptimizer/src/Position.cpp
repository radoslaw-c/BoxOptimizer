#include "Position.h"

bool operator== (const Position_T& pos1, const Position_T& pos2)
{
	return pos1.pos_length == pos2.pos_length && pos1.pos_width == pos2.pos_width &&
		pos1.layer == pos2.layer;
}

bool operator!= (const Position_T& pos1, const Position_T& pos2)
{
	return !(pos1 == pos2);
}