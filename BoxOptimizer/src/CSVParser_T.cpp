#include "CSVParser_T.h"

CSVParser_T::CSVParser_T()
{
}

CSVParser_T::CSVParser_T(std::string dataFilePath)
{
	dataFile.open(dataFilePath);

	if (dataFile.is_open())
	{
		std::string line;
		std::getline(dataFile, line);

		while (std::getline(dataFile, line))
		{
			if (!dataFrame.AppednData(line))
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
	auto values = data | std::views::split(';');

	for (auto&& rawValue : values)
	{
		auto value = std::string(&*rawValue.begin(), std::ranges::distance(rawValue));

		if (dataCounter % 9 == 0 && std::stoi(value) != boxID && boxID != -1)
			return false;

		switch (dataCounter % 9)
		{
		case 0:
			if (boxID == -1)
				boxID = std::stoi(value);
			break;

		case 1:
			height.push_back(std::stoi(value));
			break;

		case 2:
			elementName.push_back(value);
			break;

		case 3:
			length.push_back(std::stoi(value));
			break;

		case 4:
			width.push_back(std::stoi(value));
			break;

		case 5:
			numberOfElements.push_back(std::stoi(value));
			break;

		case 6:
			// nothing to do here
			break;

		case 7:
			if (productName.empty())
				productName = value;
			break;

		case 8:
			if (clientID.empty())
				clientID = value;
			break;

		}
		++dataCounter;
	}
	return true;
}
