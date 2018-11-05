#include "MapFileGenerator.h"

MapFileGenerator::MapFileGenerator()
	:
	m_fileName("Maps/")
{
}

void MapFileGenerator::Generate()
{
	using std::cout;
	using std::endl;
	using std::cerr;
	using std::ofstream;

	cout << "Invoked Generate method" << endl; // debug info
	cout << Foreground::GetTilesContainer().size() << endl; //debug info

	ofstream foregroundOutputFile;
	ofstream backgroundOutputFile;

	foregroundOutputFile.open(m_fileName + "foreground_platformer.txt");
	backgroundOutputFile.open(m_fileName + "background_platformer.txt");

	if (!foregroundOutputFile.is_open())
		cerr << "Could not open foreground_" << m_fileName << " file to generate map" << endl;
	if (!backgroundOutputFile.is_open())
		cerr << "Could not open background_" << m_fileName << " file to generate map" << endl;

	std::string foregroundOutputLine;
	std::string backgroundOutputLine;
	for (int y = 0; y < 120; ++y)
	{
		foregroundOutputLine.clear();
		backgroundOutputLine.clear();
		for (int x = 0; x < 400; ++x)
		{
			if (Foreground::CheckIfTileExists(x, y, Mode::FOREGROUND))
				foregroundOutputLine += char(Foreground::GetTileAtCoords(x, y, Mode::FOREGROUND).blockType);
			else
				foregroundOutputLine.append(" ");

			if (Foreground::CheckIfTileExists(x, y, Mode::BACKGROUND))
				backgroundOutputLine += char(Foreground::GetTileAtCoords(x, y, Mode::BACKGROUND).blockType);
			else
				backgroundOutputLine.append(" ");
		}
		foregroundOutputFile << foregroundOutputLine << endl;
		backgroundOutputFile << backgroundOutputLine << endl;
	}
	foregroundOutputFile.close();
	backgroundOutputFile.close();

	cout << "Done generating text files" << endl;
}
