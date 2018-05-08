#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "TextureLoader.h"

class MapFileGenerator
{
public:
	MapFileGenerator();
	void Generate(std::vector<std::vector<int>>&);

private:
	bool CheckIfAnyTilePositionMatchesGivenCoords(int x_coord, int y_coord, std::vector<std::vector<int>>&);
	std::vector<int> GetTileAtGivenCoords(int x, int y, std::vector<std::vector<int>>&);

private:
	std::string m_fileName;
};
