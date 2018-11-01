#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Interface/Foreground.h"

class MapFileGenerator
{
public:
	MapFileGenerator();
	void Generate();

private:
	bool CheckIfAnyTilePositionMatchesGivenCoords(int, int)const;

	template<typename T>
	T GetTileAtGivenCoords(int x, int y)const;
private:
	std::string m_fileName;
};
