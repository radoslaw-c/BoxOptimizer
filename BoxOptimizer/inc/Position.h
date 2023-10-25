#pragma once

class Position_T
{
public:
	Position_T() 
	{
		pos_width = -1;
		pos_length = -1;
		layer = -1;
	}

	Position_T(float width, float length)
	{
		pos_width = width;
		pos_length = length;
	}

	Position_T(float width, float length, short layer)
	{
		pos_width = width;
		pos_length = length;
		this->layer = layer;
	}

	float pos_width, pos_length;
	short layer = 0;
};

bool operator== (const Position_T& pos1, const Position_T& pos2);
bool operator!= (const Position_T& pos1, const Position_T& pos2);