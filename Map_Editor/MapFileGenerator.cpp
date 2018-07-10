#include "MapFileGenerator.h"

MapFileGenerator::MapFileGenerator()
	:
	m_fileName("platformer.txt")
{
}

void MapFileGenerator::Generate(std::vector< std::vector<int>>& tiles)
{
	using std::cout;
	using std::endl;
	using std::cerr;
	using std::ofstream;

	cout << "Invoked Generate method" << endl; // debug info
	cout << tiles.size() << endl; //debug info

	ofstream outputFile;
	outputFile.open(m_fileName);

	if (!outputFile.is_open())
		cerr << "Could not open " << m_fileName << " file to generate map" << endl;

	std::string outputLine;
	for (int y = 0; y < 120; ++y)
	{
		outputLine.clear();
		for (int x = 0; x < 400; ++x)
		{
			if (CheckIfAnyTilePositionMatchesGivenCoords(x, y, tiles))
			{
				switch (GetTileAtGivenCoords(x, y, tiles)[2])
				{
				case BlockTypes::ENUM_GRASS:
					outputLine += "1";
					break;
				case BlockTypes::ENUM_DIRT:
					outputLine += "2";
					break;
				case BlockTypes::ENUM_GRASS_ULDR:
					outputLine += "3";
					break;
				case BlockTypes::ENUM_GRASS_DLTR:
					outputLine += "4";
					break;
				case BlockTypes::ENUM_STONE:
					outputLine += "5";
					break;
				case BlockTypes::ENUM_DIRT_DLTR:
					outputLine += "6";
					break;
				case BlockTypes::ENUM_DIRT_TLDR:
					outputLine += "7";
					break;
				case BlockTypes::ENUM_TERRAIN_PLATFORM_LEFT:
					outputLine += "8";
				default:
					break;
				}
			}
			else
				outputLine.append(" ");
		}
		outputFile << outputLine << endl;
	}
	outputFile.close();
	cout << "Done generating text file" << endl;
}

bool MapFileGenerator::CheckIfAnyTilePositionMatchesGivenCoords(int x, int y, std::vector <std::vector<int> >& tiles_info) const
{
	for (auto &it : tiles_info)
	{
		if (it[0] == x && it[1] == y)
			return true;
	}
	return false;
}

std::vector<int> MapFileGenerator::GetTileAtGivenCoords(int x, int y, std::vector<std::vector<int>>& tiles_info) const
{
	for (auto &it : tiles_info)
	{
		if (it[0] == x && it[1] == y)
			return it;
	}
}
