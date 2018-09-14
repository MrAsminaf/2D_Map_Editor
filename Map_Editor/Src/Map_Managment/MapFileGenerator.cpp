#include "MapFileGenerator.h"

MapFileGenerator::MapFileGenerator()
	:
	m_fileName("Maps/platformer.txt")
{
}

void MapFileGenerator::Generate()
{
	using std::cout;
	using std::endl;
	using std::cerr;
	using std::ofstream;

	cout << "Invoked Generate method" << endl; // debug info
	cout << Interface::GetTilesContainer().size() << endl; //debug info

	ofstream outputFile;
	outputFile.open(m_fileName);

	if (!outputFile.is_open())
		cerr << "Could not open " << m_fileName << " file to generate map" << endl;

	std::string outputLine;
	constexpr int BLOCK_ID = 2;
	for (int y = 0; y < 120; ++y)
	{
		outputLine.clear();
		for (int x = 0; x < 400; ++x)
		{
			if (CheckIfAnyTilePositionMatchesGivenCoords(x, y))
				outputLine += char(GetTileAtGivenCoords(x, y)[BLOCK_ID]);
			else
				outputLine.append(" ");
		}
		outputFile << outputLine << endl;
	}
	outputFile.close();
	cout << "Done generating text file" << endl;
}

bool MapFileGenerator::CheckIfAnyTilePositionMatchesGivenCoords(int x, int y) const
{
	for (auto &it : Interface::GetTilesContainer())
	{
		if (it[0] == x && it[1] == y)
			return true;
	}
	return false;
}

std::vector<int> MapFileGenerator::GetTileAtGivenCoords(int x, int y) const
{
	for (auto &it : Interface::GetTilesContainer())
	{
		if (it[0] == x && it[1] == y)
			return it;
	}
}
