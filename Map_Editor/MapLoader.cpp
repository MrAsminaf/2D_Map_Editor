#include "MapLoader.h"

void ExternalMapLoader::LoadMapFromFile(const std::string filename, std::vector<std::vector<int>>& tilesVector)
{
	std::cout << "LoadMapFromFile: " << filename << std::endl;
	ClearVectorBeforeLoadingMap(tilesVector);
	std::ifstream inFile;
	inFile.open(filename);

	if (!inFile.is_open())
		std::cerr << "Could not open " << filename << std::endl;

	std::string line;
	int y = 0;
	while (std::getline(inFile, line))
	{
		for (auto i = 0; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				std::vector<int> temp;
				temp.push_back(i);
				temp.push_back(y);
				temp.push_back(line[i]-'0');
				tilesVector.push_back(temp);
			}
		}
		++y;
	}
	inFile.close();
	std::cout << "Loaded map. Current size: " << tilesVector.size() << std::endl;
}

void ExternalMapLoader::ClearVectorBeforeLoadingMap(std::vector<std::vector<int>>& tilesVector)
{
	tilesVector.clear();
}
