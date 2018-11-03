#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "Interface/Foreground.h"

class ExternalMapLoader
{
public:
	void LoadMapFromFile(const std::string filename, std::vector<Block>& tilesVector);
private:
	template<typename T>
	void ClearVectorBeforeLoadingMap(std::vector<T>& tilesVector);
};