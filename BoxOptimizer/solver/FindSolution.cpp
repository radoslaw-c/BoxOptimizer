#include "Solver.h"




void Solver_T::Solve()
{
	FindSolutions();
	//find solution with lowest area
}

void Solver_T::FindSolutions()
{
	Element_T Element = ElementList[0];
	ElementPlacement_T ElementPlacement;

	ElementPlacement.id = Element.id();
	ElementPlacement.width = Element.width();
	ElementPlacement.length = Element.length();

	//set position of 1st element
	ElementPlacement.position.width = possiblePlacements.front()[0];
	ElementPlacement.position.length = possiblePlacements.front()[1];

	Solution_T solution;
	solution.placement.push_back(ElementPlacement);	//i to jest element wspólny dla ka¿dego mo¿liwego rozwi¹zania

	FindPossiblePlacements(solution);

	for (int i = 1; i < numberOfElements; i++)	//pomijamy pierwszy bo to zawsze od niego zaczynamy
	{

	}
}

void Solver_T::FindPossiblePlacements(const Solution_T solution)
{
	//w tym miejscu mam wektor placement, z³o¿ony z element_placement, czyli pocz¹tku i koñca

	//
	// 1. znaleŸæ w wektorze possiblePlacements pozycjê, na której jest ostatni element
	// 2. usun¹æ j¹
	// 3. zast¹piæ nowymi wierzcho³kami 
	//

	//for (auto possiblePlacement : possiblePlacements)
	for (auto it = possiblePlacements.begin(); it < possiblePlacements.end(); it++)
	{
		auto possiblePlacement = *it;
		if (possiblePlacement[0] == solution.placement.back().position.width &&
			possiblePlacement[1] == solution.placement.back().position.length)
		{
			possiblePlacements.erase(it);
			break;
			std::cout << "TEST\n";
		}
	}

	float newPlacement[2] = { solution.placement.back().position.length, solution.placement.back().width};
	possiblePlacements.push_back(newPlacement);

	newPlacement[0] = solution.placement.back().length;
	newPlacement[1] = solution.placement.back().position.width;
	possiblePlacements.push_back(newPlacement);

}