#include <iostream>
#include "Solver.h"
#include "ConsoleVisualiser_T.h"

int main()
{
    Solver_T Solver;
    Solver.InitializeElementsManually();
    Solver.Solve();
}
