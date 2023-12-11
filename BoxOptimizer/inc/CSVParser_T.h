#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <ranges>

#include "DataFrame_T.h"

class CSVParser_T
{
public:
	CSVParser_T();
	CSVParser_T(std::string dataFilePath);

	// getters
	DataFrame_T DataFrame() const { return dataFrame; };

private:
	// fields
	std::ifstream dataFile;
	DataFrame_T dataFrame;

	// methods


};

