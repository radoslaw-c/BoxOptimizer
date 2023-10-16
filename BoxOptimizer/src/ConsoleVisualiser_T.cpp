#include "ConsoleVisualiser_T.h"

static void print_solution(char solution[][50], const Solution_T& Solution);
std::vector<Position_T> FindAvailableSlots(Node_T currentNode);

ConsoleVisualiser_T::ConsoleVisualiser_T(Solution_T Solution)
{
	this->Solution = Solution;
}

void ConsoleVisualiser_T::DrawSolution()
{
	char solutionMatrix[50][50];

	Node_T* Node = Solution.SolutionNode;
	while (Node != NULL)
	{
		const Element_T* Element = &Node->Element;
		Position_T ElementEnd = Position_T(Node->Element.getPosition().pos_width + Node->Element.getWidth(),
			Node->Element.getPosition().pos_length + Node->Element.getLength());

		for (int len = Node->Element.getPosition().pos_length;
			len <= (int)ElementEnd.pos_length; len++)
		{
			for (int width = Node->Element.getPosition().pos_width;
				width <= (int)ElementEnd.pos_width; width++)
			{
				if (len == Node->Element.getPosition().pos_length
					|| len == ElementEnd.pos_length)
				{
					if (width == Node->Element.getPosition().pos_width ||
						width == ElementEnd.pos_width)
					{
						solutionMatrix[len][width] = '+';
					}
					else
					{
						solutionMatrix[len][width] = '-';
					}
				}
				else
				{
					if (width == Node->Element.getPosition().pos_width ||
						width == ElementEnd.pos_width)
						solutionMatrix[len][width] = '|';
					else
					{
						if (len == std::floor(Node->Element.getLength() / 2 + Node->Element.getPosition().pos_length) &&
							width == std::floor(Node->Element.getWidth() / 2) + Node->Element.getPosition().pos_width)
							solutionMatrix[len][width] = Node->Element.getId() + 48;
						else
							solutionMatrix[len][width] = ' ';
					}
				}
			}
		}
		Node = Node->ParentNode;
	}
	print_solution(solutionMatrix, Solution);
 }

static void print_solution(char solutionMatrix[][50], const Solution_T& Solution)
{
	auto outline = FindAvailableSlots(*Solution.SolutionNode);

	float max_width = 0, max_len = 0;

	for (auto point : outline)
	{
		if (point.pos_width > max_width)
			max_width = point.pos_width;
		if (point.pos_length > max_len)
			max_len = point.pos_length;
	}

	for (int i = 0; i <= max_len; i++)
	{
		for (int j = 0; j <= max_width; j++)
		{
			if (solutionMatrix[i][j] != -52)
				std::cout << solutionMatrix[i][j];
			else
				std::cout << ' ';
		}
		std::cout << std::endl;
	}
}

std::vector<Position_T> FindAvailableSlots(Node_T currentNode)
{
	std::vector<Position_T> availableSlots;
	Position_T positionOfChildNode;

	while (true)
	{
		Position_T availableSlot1;
		availableSlot1.pos_width = currentNode.Element.getWidth() +
			currentNode.Element.getPosition().pos_width;
		availableSlot1.pos_length = currentNode.Element.getPosition().pos_length;

		if (availableSlot1 != positionOfChildNode)
		{
			availableSlots.push_back(availableSlot1);
		}

		Position_T availableSlot2;
		availableSlot2.pos_width = currentNode.Element.getPosition().pos_width;
		availableSlot2.pos_length = currentNode.Element.getLength() +
			currentNode.Element.getPosition().pos_length;

		if (availableSlot2 != positionOfChildNode)
		{
			availableSlots.push_back(availableSlot2);
		}

		positionOfChildNode = currentNode.Element.getPosition();

		if (currentNode.ParentNode != NULL)
			currentNode = *currentNode.ParentNode;
		else
			break;
	}

	return availableSlots;
}