#pragma once
#include <string>
#include <vector>
#include <ranges>

class DataFrame_T
{
public:
	bool AppednData(std::string& data);

	// getters
	unsigned int ElementsCount() const { return elementsCount; };
	float Length(unsigned int it) const { return length[it]; };
	float Width(unsigned int it) const { return width[it]; };
	float Height(unsigned int it) const { return height[it]; };

	std::vector<float> Length() const { return length; };
	std::vector<float> Width() const { return width; };
	std::vector<float> Height() const { return height; };

private:
	unsigned int boxID = -1;
	std::string productName;
	std::string clientID;
	std::vector<float> height;
	std::vector<std::string> elementName;
	std::vector<float> length;
	std::vector<float> width;
	std::vector<unsigned int> numberOfElements;
	unsigned int dataCounter = 0;
	unsigned int elementsCount = 0;
};
