#pragma once
#include "Node_T.h"
#include "CalculateOutlineArea.h"
#include <limits>
#include <algorithm>
#include <iterator>

#include <iostream>

typedef std::vector<const Node_T*> Layer_T;
typedef std::vector<Layer_T> LayerMap_T;

typedef std::vector<Vertex_T> Contour_T;
typedef std::vector<Contour_T> LayerContours_T;

class Solution_T
{
public:
	Solution_T(Node_T* Node);
	Solution_T(Node_T* Node, int id);
	Solution_T() {};
	bool IsValid() const { return layerValid; }
	Node_T* SolutionNode;
	int id = -1;
	float getOutlineArea() { return outlineArea; }

private:
	void Classify();
	void LayerValidity();
	void CreateLayerMap();
	void GetLayerContours();
	bool CheckOverhangValid() const;

	float outlineArea = std::numeric_limits<float>::max();
	bool layerValid = false;

	LayerMap_T LayerMap;
	LayerContours_T LayerContours;
};

typedef std::vector<Solution_T> SolutionList_T;
