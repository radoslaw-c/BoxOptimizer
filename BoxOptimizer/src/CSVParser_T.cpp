#include "CSVParser_T.h"

CSVParser_T::CSVParser_T()
{
}

CSVParser_T::CSVParser_T(std::string dataFilePath)
{
	dataFile.open(dataFilePath);

	if (dataFile.is_open())
	{
		std::string data;
		std::getline(dataFile, data);

		while (std::getline(dataFile, data, ';'))
		{
			if (!dataFrame.AppednData(data))
				break;
		}
	}
}

void CSVParser_T::InterpretDataLine(std::string& line)
{
}

bool DataFrame_T::AppednData(std::string& data)
{
	// TODO check if is a valid number

	if (dataCounter % 9 == 0 && std::stoi(data) != boxID && boxID != -1)
		return false;

	switch (dataCounter % 9)
	{
	case 0:
		if (boxID == -1)
			boxID = std::stoi(data);
		break;

	case 1:
		height.push_back(std::stoi(data));
		break;

	case 2:
		elementName.push_back(data);
		break;

	case 3:
		length.push_back(std::stoi(data));
		break;

	case 4:
		width.push_back(std::stoi(data));
		break;

	case 5:
		numberOfElements.push_back(std::stoi(data));
		break;

	case 6:
		// nothing to do here
		break;

	case 7:
		if (productName.empty())
			productName = data;
		break;

	case 8:
		if (clientID.empty())
		{
			data.pop_back();
			clientID = data;
		}

		//dataCounter = 0;
		break;

	}
	++dataCounter;
	return true;
}
