#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "TextureManager.h"
#include "Interface.h"

class MapFileGenerator
{
public:
	MapFileGenerator();
	void Generate();

private:
	bool CheckIfAnyTilePositionMatchesGivenCoords(int, int)const;
	std::vector<int> GetTileAtGivenCoords(int x, int y)const;

private:
	std::string m_fileName;
};
