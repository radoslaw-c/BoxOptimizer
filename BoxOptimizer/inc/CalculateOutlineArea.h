#pragma once
#include "Node_T.h"

struct BoxDimmensions
{
	BoxDimmensions(float width, float length, float height)
	{
		boxWidth = width;
		boxLength = length;
		boxHeight = height;
	}

	float boxWidth = 0;
	float boxLength = 0;
	float boxHeight = 0;
};

float CalculateOutlineArea(const Node_T* Node);
BoxDimmensions CalculateBoxDimmensions(const Node_T* Node);
