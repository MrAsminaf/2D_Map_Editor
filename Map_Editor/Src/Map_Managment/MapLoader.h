#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

class ExternalMapLoader
{
public:
	void LoadMapFromFile(const std::string filename, std::vector<std::vector<int>>& tilesVector);

private:
	void ClearVectorBeforeLoadingMap(std::vector<std::vector<int>>& tilesVector);

private:
	std::vector<std::vector<int>>* pointy;
};