#include "ConsoleVisualiser_T.h"

ConsoleVisualiser_T::ConsoleVisualiser_T(Solution_T Solution)
{
	this->Solution = Solution;
}

void ConsoleVisualiser_T::DrawSolution()
{
	char solutionMatrix[50][50];

	Node_T* Node = Solution.SolutionNode;
	while (true)
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
					{
						solutionMatrix[len][width] = '+';
					}
					else
					{
						solutionMatrix[len][width] = '-';
					}
				}
			}

		}


		if (Solution.SolutionNode->ParentNode == NULL)
			break;
		else
			Node = Node->ParentNode;
	}


}


/*
for (int len = 1; len <= 2* element.getLength(); len++)
{
	for (int width = 1; width <= 2 * element.getWidth(); width++)
	{
		if (len == 1 || len == 2* element.getLength())
		{
			if (width == 1 || width == 2 * element.getWidth())
				std::cout << "+";
			else
				std::cout << "-";
		}
		else
		{
			if (width == 1 || width == 2 * element.getWidth())
				std::cout << "|";
			else
			{
				if (len == element.getLength() && width == element.getWidth())
					std::cout << element.getId();
				else
					std::cout << " ";
			}
		}

	}
	std::cout << std::endl;
}
*/