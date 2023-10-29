#pragma once
#include <cmath>

class Position_T
{
public:
	Position_T() 
	{
		pos_width = -1;
		pos_length = -1;
	}

	Position_T(float width, float length)
	{
		pos_width = width;
		pos_length = length;
	}

	Position_T(float width, float length, float height)
	{
		pos_width = width;
		pos_length = length;
		pos_height = height;
	}

	float pos_width = 0, pos_length = 0, pos_height = 0;;
	short layer = -1;
};

bool operator== (const Position_T& pos1, const Position_T& pos2);
bool operator!= (const Position_T& pos1, const Position_T& pos2);
bool operator< (const Position_T& pos1, const Position_T& pos2);

bool comparePositions(const Position_T& pos1, const Position_T& pos2);
bool comaprePositions_widthLess(const Position_T& pos1, const Position_T& pos2);
bool comaprePositions_lengthLess(const Position_T& pos1, const Position_T& pos2);
float positionDistance(const Position_T& pos1, const Position_T& pos2, bool use3D = false);
