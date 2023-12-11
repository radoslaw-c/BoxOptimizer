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
