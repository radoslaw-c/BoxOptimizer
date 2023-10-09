#include "Position.h"

bool operator== (Position_T pos1, Position_T pos2)
{
	return pos1.pos_length == pos2.pos_length && pos1.pos_width == pos2.pos_width;
}

bool operator!= (Position_T pos1, Position_T pos2)
{
	return !(pos1 == pos2);
}