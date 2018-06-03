#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "TextureManager.h"
#include "MapFileGenerator.h"
#include "MapLoader.h"
#include "BlockTypes.h"

class GUI
{
public:
	GUI(sf::RectangleShape& rs, BlockTypes& current_block, std::vector< std::vector<int> >& );
	void Update();
	void HandleEvents(sf::Event sf_event);

private:
	void InitPanel(sf::RectangleShape& rs, BlockTypes& current_block, std::vector<std::vector<int>>&);
	void CreateButtonsForChoosingBlocks(sf::RectangleShape& rs, BlockTypes& current_block);
	void AddImageToPanel(std::string filepath);
	void AddButtonForChosingBlock(std::string filepath, sf::RectangleShape& rs, BlockTypes& current_block, BlockTypes& block_being_chosen);
	void CreateOpenButton(sfg::Desktop& desktop, std::vector<std::vector<int>>&);

private:
	sfg::Window::Ptr m_sfgWindow;
	sfg::Box::Ptr m_sfgBox;
	sfg::Box::Ptr m_scrolledWindowBox;
	sfg::Desktop desktop;
	MapFileGenerator m_generator;
	ExternalMapLoader m_mapFromFileLoader;
	const float m_spacingBetweenWidgets;
};
