#pragma once
#include <string>
#include <fstream>
#include <vector>

class DataFrame_T
{
public:
	unsigned int boxID = -1;
	std::string productName;
	std::string clientID;
	std::vector<float> height;
	std::vector<std::string> elementName;
	std::vector<float> length;
	std::vector<float> width;
	std::vector<unsigned int> numberOfElements;

	bool AppednData(std::string& data);

private:
	unsigned int dataCounter = 0;
};

class CSVParser_T
{
public:
	CSVParser_T();
	CSVParser_T(std::string dataFilePath);

private:
	// fields
	std::ifstream dataFile;
	DataFrame_T dataFrame;

	// methods
	void InterpretDataLine(std::string& line);


};

