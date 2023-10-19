#pragma once
#include <iostream>
#include "Solution_T.h"

class ConsoleVisualiser_T
{
public:
	ConsoleVisualiser_T(Solution_T Solution);
	void DrawSolution();
	void PrintSolutionDetails();

private:
	Solution_T Solution;
	

};

