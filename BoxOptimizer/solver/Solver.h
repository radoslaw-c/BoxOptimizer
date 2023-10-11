//#include "Element.h"
#include "Calibrations_T.h"
#include "Node_T.h"
#include "Solution_T.h"
#include <vector>
#include <iostream>

class Solver_T
{
public:
	Solver_T();
	void InitializeElementsManually();

	void Solve(); // :)

private:
	void FindSolutions();
	void InitializeSolutionTree();
	void PopulateSolutionTree(Element_T Element, Node_T& ChildNodes);
	std::vector<Position_T> FindAvailableSlots(Node_T currentNode);
	std::vector<Element_T> GetAncestors(Node_T node);
	bool IsLastNode(Node_T Node);
	bool IsAncestor(Element_T Element, Node_T Node);

	void CalculateTotalElementArea();
	float CalculateOutlineArea(Node_T Node);
	bool NodeValid(Node_T Node);
	

	std::vector<Element_T> ElementList;
	//std::vector<Node_T*> SolutionList;
	std::vector<Solution_T> SolutionList;
	int numberOfElements = 0;
	float totalElementArea = 0;

	Calibrations_T calib;

	Node_T RootNode;
};

