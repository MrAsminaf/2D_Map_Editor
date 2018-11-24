#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Interface/Foreground.h"

class MapFileGenerator
{
public:
	MapFileGenerator();
	void Generate();
private:
	std::string m_fileName;
};
