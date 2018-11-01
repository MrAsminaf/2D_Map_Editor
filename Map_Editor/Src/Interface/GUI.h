#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "imgui.h"
#include "imgui-sfml-master/imgui-SFML.h"
#include "Map_Managment/MapFileGenerator.h"
#include "Map_Managment/MapLoader.h"
#include "Background.h"

class GUI
{
public:
	void Update(sf::Color& bg_color);
private:
	MapFileGenerator m_generator;
	ExternalMapLoader m_mapFromFileLoader;
	float m_backgroundColorBuffer[3] = { 0.f, 0.f, 0.f };
	float m_netColorBuffer[3] = { 0.f, 0.f, 0.f };
};
