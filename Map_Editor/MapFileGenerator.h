#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "TextureManager.h"

class MapFileGenerator
{
public:
	MapFileGenerator();
	void Generate(std::vector<std::vector<int>>&);

private:
	bool CheckIfAnyTilePositionMatchesGivenCoords(int, int, std::vector<std::vector<int>>&)const;
	std::vector<int> GetTileAtGivenCoords(int x, int y, std::vector<std::vector<int>>&)const;

private:
	std::string m_fileName;
};
