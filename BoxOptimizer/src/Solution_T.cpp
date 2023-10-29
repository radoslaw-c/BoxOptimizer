#include "Solution_T.h"

static std::vector<Vertex_T> findElementVertexes(const Node_T* Node);

Solution_T::Solution_T(Node_T* Node)
{
	SolutionNode = Node;
	Classify();
}

Solution_T::Solution_T(Node_T* Node, int id)
{
	SolutionNode = Node;
	this->id = id;
	Classify();
}

void Solution_T::Classify()
{
	outlineArea = CalculateOutlineArea(SolutionNode);
	LayerValidity();
}

void Solution_T::LayerValidity()
{
	CreateLayerMap();
	GetLayerContours();

	// 1. Check for overhang
	const bool overhangValid = CheckOverhangValid();

	layerValid = overhangValid && true;
}

void Solution_T::CreateLayerMap()
{
	LayerMap.resize(SolutionNode->TreeLevel); // definietly more than necessary

	auto currentNode = SolutionNode;
	while (currentNode != NULL)
	{
		LayerMap[currentNode->layer].push_back(currentNode);

		currentNode = currentNode->ParentNode;
	}
}

void Solution_T::GetLayerContours()
{
	for (const Layer_T& Layer : LayerMap)
	{
		Contour_T contour;

		for (const Node_T* Node : Layer)
		{
			if (!std::is_sorted(contour.begin(), contour.end(), comparePositions))
				std::sort(contour.begin(), contour.end(), comparePositions);
			auto elementCountour = findElementVertexes(Node);

			Contour_T contourIntersection;
			std::set_intersection(contour.begin(), contour.end(),
				elementCountour.begin(), elementCountour.end(),
				std::back_inserter(contourIntersection), comparePositions);

			Contour_T contourUnion;			

			std::set_union(contour.begin(), contour.end(),
				elementCountour.begin(), elementCountour.end(),
				std::back_inserter(contourUnion), comparePositions);

			std::sort(contourUnion.begin(), contourUnion.end(), comparePositions);

			std::set_difference(contourUnion.begin(), contourUnion.end(),
				contourIntersection.begin(), contourIntersection.end(),
				std::back_inserter(contour), comparePositions);
		}
		std::sort(contour.begin(), contour.end(), comparePositions);
		LayerContours.push_back(contour);
	}
}

static std::vector<Vertex_T> findElementVertexes(const Node_T* currentNode)
{
	//TODO add a way to handle non-rectangles
	auto vertex_1 = Vertex_T(currentNode->Position.pos_width, currentNode->Position.pos_length, 
		currentNode->Element.getId());
	vertex_1.layer = currentNode->layer;

	auto vertex_2 = Vertex_T(currentNode->Position.pos_width + currentNode->Element.getWidth(),
		currentNode->Position.pos_length, currentNode->Element.getId());
	vertex_2.layer = currentNode->layer;

	auto vertex_3 = Vertex_T(currentNode->Position.pos_width,
		currentNode->Position.pos_length + currentNode->Element.getLength(), currentNode->Element.getId());
	vertex_3.layer = currentNode->layer;

	auto vertex_4 = Vertex_T(currentNode->Position.pos_width + currentNode->Element.getWidth(),
		currentNode->Position.pos_length + currentNode->Element.getLength(), currentNode->Element.getId());
	vertex_4.layer = currentNode->layer;

	std::vector<Vertex_T> elementVertexes = {vertex_1, vertex_2,
		vertex_3, vertex_4};

	std::sort(elementVertexes.begin(), elementVertexes.end(), comparePositions);

	return elementVertexes;
}

bool Solution_T::CheckOverhangValid() const
{
	for (auto it = 1; it < LayerContours.size(); it++)
	{
		const auto& prevLayerContour = LayerContours[it - 1];
		const auto& currentLayerContour = LayerContours[it];

		//check if upper layer extends further
		std::vector<Vertex_T> extremePositions_currentLayer;
		std::set_difference(currentLayerContour.begin(), currentLayerContour.end(),
			prevLayerContour.begin(), prevLayerContour.end(),
			std::back_inserter(extremePositions_currentLayer), comparePositions);

		std::vector<Vertex_T> extremePositions_prevLayer;
		std::set_difference(prevLayerContour.begin(), prevLayerContour.end(), 
			currentLayerContour.begin(), currentLayerContour.end(), 
			std::back_inserter(extremePositions_prevLayer), comparePositions);

		for (const auto& extremePos_currenLayer : extremePositions_currentLayer)
		{
			for (const auto& extremePos_prevLayer : extremePositions_prevLayer)
			{	 
				if (extremePos_currenLayer.pos_length == extremePos_prevLayer.pos_length)
				{
					// TODO take rotations into consideration !!!!
					
					auto distance = extremePos_currenLayer.pos_width - extremePos_prevLayer.pos_width;
					auto node = *std::find_if(LayerMap[it].begin(), LayerMap[it].end(),
						[extremePos_currenLayer](const Node_T* node)
						{
							return node->Element.getId() == extremePos_currenLayer.ElementID;
						});
					if (distance > 0.3F * node->Element.getWidth())
						return false;

				}
				else if (extremePos_currenLayer.pos_width == extremePos_prevLayer.pos_width)
				{
					auto distance = extremePos_currenLayer.pos_length - extremePos_prevLayer.pos_length;
					auto node = *std::find_if(LayerMap[it].begin(), LayerMap[it].end(),
						[extremePos_currenLayer](const Node_T* node)
						{
							return node->Element.getId() == extremePos_currenLayer.ElementID;
						});
					if (distance > 0.3F * node->Element.getLength())
						return false;
				}
			}
		}
	}
	return true;
}
