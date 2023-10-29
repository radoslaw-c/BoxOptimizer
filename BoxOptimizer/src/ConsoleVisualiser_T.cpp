#include "ConsoleVisualiser_T.h"

static void print_solution(char solution[][50][50], const Solution_T& Solution);
std::vector<Position_T> FindAvailableSlots(Node_T currentNode);

ConsoleVisualiser_T::ConsoleVisualiser_T(Solution_T Solution)
{
	this->Solution = Solution;
}

void ConsoleVisualiser_T::DrawSolution()
{
	char solutionMatrix[4][50][50];

	Node_T* Node = Solution.SolutionNode;
	while (Node != NULL)
	{
		//const Element_T* Element = &Node->Element;
		Position_T ElementEnd = Position_T(Node->Position.pos_width + Node->Element.getWidth(),
			Node->Position.pos_length + Node->Element.getLength());

		for (int len = Node->Position.pos_length;
			len <= (int)ElementEnd.pos_length; len++)
		{
			for (int width = Node->Position.pos_width;
				width <= (int)ElementEnd.pos_width; width++)
			{
				if (len == Node->Position.pos_length
					|| len == ElementEnd.pos_length)
				{
					if (width == Node->Position.pos_width ||
						width == ElementEnd.pos_width)
					{
						solutionMatrix[(int)Node->Position.pos_height][len][width] = '+';
					}
					else
					{
						solutionMatrix[(int)Node->Position.pos_height][len][width] = '-';
					}
				}
				else
				{
					if (width == Node->Position.pos_width ||
						width == ElementEnd.pos_width)
						solutionMatrix[(int)Node->Position.pos_height][len][width] = '|';
					else
					{
						if (len == std::floor(Node->Element.getLength() / 2 + Node->Position.pos_length) &&
							width == std::floor(Node->Element.getWidth() / 2) + Node->Position.pos_width)
							solutionMatrix[(int)Node->Position.pos_height][len][width] = Node->Element.getId() + 48;
						else
							solutionMatrix[(int)Node->Position.pos_height][len][width] = ' ';
					}
				}
			}
		}
		Node = Node->ParentNode;
	}
	print_solution(solutionMatrix, Solution);
 }

static void print_solution(char solutionMatrix[][50][50], const Solution_T& Solution)
{
	auto outline = FindAvailableSlots(*Solution.SolutionNode);

	float max_width = 0, max_len = 0;

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Layer ID: " << i << std::endl;
		auto layer = solutionMatrix[i];
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
				if (layer[i][j] != -52)
					std::cout << layer[i][j];
				else
					std::cout << ' ';
			}
			std::cout << std::endl;
		}
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
			currentNode.Position.pos_width;
		availableSlot1.pos_length = currentNode.Position.pos_length;

		if (availableSlot1 != positionOfChildNode)
		{
			availableSlots.push_back(availableSlot1);
		}

		Position_T availableSlot2;
		availableSlot2.pos_width = currentNode.Position.pos_width;
		availableSlot2.pos_length = currentNode.Element.getLength() +
			currentNode.Position.pos_length;

		if (availableSlot2 != positionOfChildNode)
		{
			availableSlots.push_back(availableSlot2);
		}

		positionOfChildNode = currentNode.Position;

		if (currentNode.ParentNode != NULL)
			currentNode = *currentNode.ParentNode;
		else
			break;
	}

	return availableSlots;
}

void ConsoleVisualiser_T::PrintSolutionDetails()
{
	std::cout << "Outline area: " << Solution.getOutlineArea() << std::endl;
	std::cout << "Solution ID: " << Solution.id << std::endl;
	std::cout << "Solution valid: " << Solution.IsValid() << std::endl;
	std::cout << "\n===================================\n";

}