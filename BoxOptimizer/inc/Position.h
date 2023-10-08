#pragma once
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
	float pos_width, pos_length;
};

