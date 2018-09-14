#include "MapLoader.h"

void ExternalMapLoader::LoadMapFromFile(const std::string filename, std::vector<std::vector<int>>& tilesVector)
{
	std::cout << "LoadMapFromFile: " << filename << std::endl;
	ClearVectorBeforeLoadingMap(tilesVector);
	std::ifstream inFile;
	inFile.open("Maps/"+filename);

	if (!inFile.is_open())
	{
		std::cerr << "Could not open " << filename << std::endl;
		return;
	}

	std::string line;
	int y = 0;
	while (std::getline(inFile, line))
	{
		for (auto x = 0; x < line.size(); ++x)
		{
			if (line[x] != ' ')
			{
				std::vector<int> tempTile;
				tempTile.push_back(x);
				tempTile.push_back(y);
				tempTile.push_back(line[x]);
				tilesVector.push_back(tempTile);
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
