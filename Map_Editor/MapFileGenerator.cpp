#include "MapFileGenerator.h"

MapFileGenerator::MapFileGenerator()
	:
	m_fileName("map.txt")
{
}

void MapFileGenerator::Generate(std::vector< std::vector<int>>& tiles_info)
{
	std::cout << "Invoked Generate method" << std::endl; // debug info
	std::cout << tiles_info.size() << std::endl; //debug info

	std::ofstream outputToMapTxtFile;
	outputToMapTxtFile.open(m_fileName);

	if (!outputToMapTxtFile.is_open())
		std::cout << "Could not open " << m_fileName << " file to generate map" << std::endl;

	std::string outputLine;
	for (int y_coord = 0; y_coord < 200; ++y_coord)
	{
		outputLine.clear();
		for (int x_coord = 0; x_coord < 400; ++x_coord)
		{
			if (CheckIfAnyTilePositionMatchesGivenCoords(x_coord, y_coord, tiles_info))
			{
				switch (GetTileAtGivenCoords(x_coord, y_coord, tiles_info)[2])
				{
				case TextureLoader::ENUM_GRASS:
					outputLine.append("1");
					break;
				case TextureLoader::ENUM_DIRT:
					outputLine.append("2");
					break;
				case TextureLoader::ENUM_GRASS_ULDR:
					outputLine.append("3");
					break;
				case TextureLoader::ENUM_GRASS_DLTR:
					outputLine.append("4");
					break;
				case TextureLoader::ENUM_STONE:
					outputLine.append("5");
					break;
				case TextureLoader::ENUM_DIRT_DLTR:
					outputLine.append("6");
					break;
				case TextureLoader::ENUM_DIRT_TLDR:
					outputLine.append("7");
					break;
				default:
					break;
				}
			}
			else
				outputLine.append(" ");
		}
		outputToMapTxtFile << outputLine << std::endl;
	}
	outputToMapTxtFile.close();
	std::cout << "Done generating text file" << std::endl;
}

bool MapFileGenerator::CheckIfAnyTilePositionMatchesGivenCoords(int x_coord, int y_coord, std::vector<std::vector<int>>& tiles_info)
{
	for (auto &it : tiles_info)
	{
		if (it[0] == x_coord && it[1] == y_coord)
			return true;
	}
	return false;
}

std::vector<int> MapFileGenerator::GetTileAtGivenCoords(int x, int y, std::vector<std::vector<int>>& tiles_info)
{
	for (auto &it : tiles_info)
	{
		if (it[0] == x && it[1] == y)
			return it;
	}
}
