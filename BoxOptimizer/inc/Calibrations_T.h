#pragma once
class Calibrations_T
{
public:
	const float maxAllowedArea = 1.5; //How much can area of solution be greater than sum of areas of elements
	
	const float layerTolerance_down = 0.2;	//
	const float layerTolerance_up = 0.2;
};