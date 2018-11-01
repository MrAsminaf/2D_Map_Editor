#include "MapLoader.h"

void ExternalMapLoader::LoadMapFromFile(const std::string filename, std::vector<ForegroundBlock>& tilesVector)
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
				ForegroundBlock temp;
				temp.x = x;
				temp.y = y;
				temp.blockType = BlockTypes(line[x]);
				tilesVector.push_back(temp);
			}
		}
		++y;
	}
	inFile.close();
	std::cout << "Loaded map. Current size: " << tilesVector.size() << std::endl;
}

template<typename T>
void ExternalMapLoader::ClearVectorBeforeLoadingMap(std::vector<T>& tilesVector)
{
	tilesVector.clear();
}
