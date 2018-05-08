#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "TextureLoader.h"
#include "MapFileGenerator.h"
#include "ExternalMapLoader.h"

class GUI
{
public:
	GUI(sf::RectangleShape& rs, TextureLoader::ID& current_block, std::vector<std::vector<int>>& );
	void Update();
	void HandleEvents(sf::Event sf_event);

private:
	void InitPanel(sf::RectangleShape& rs, TextureLoader::ID& current_block, std::vector<std::vector<int>>&);
	void CreateButtonsForChoosingBlocks(sf::RectangleShape& rs, TextureLoader::ID& current_block);
	void AddImageToPanel(std::string filepath);
	void AddButtonForChosingBlock(std::string filepath, sf::RectangleShape& rs, TextureLoader::ID& current_block, TextureLoader::ID& block_being_chosen);
	void CreateOpenButton(sfg::Desktop& desktop, std::vector<std::vector<int>>&);

private:
	sfg::Window::Ptr m_sfgWindow;
	sfg::Box::Ptr m_sfgBox;
	sfg::Box::Ptr m_scrolledWindowBox;
	sfg::Desktop desktop;
	MapFileGenerator m_generator;
	ExternalMapLoader m_mapFromFileLoader;
	const float m_spacingBetweenWidgets = 7.0f;
};
