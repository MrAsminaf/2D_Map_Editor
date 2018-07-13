#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "MapFileGenerator.h"
#include "MapLoader.h"
#include "BlockTypes.h"
#include "Interface.h"

class GUI
{
public:
	GUI();
	void Update();
	void HandleEvents(sf::Event sf_event);

private:
	void InitPanel();
	void CreateButtonsForChoosingBlocks();
	void AddButtonForChosingBlock(const std::string& filepath, const BlockTypes& block_being_chosen);
	void CreateOpenButton();

private:
	sfg::Window::Ptr m_sfgWindow;
	sfg::Box::Ptr m_sfgBox;
	sfg::Desktop desktop;
	MapFileGenerator m_generator;
	ExternalMapLoader m_mapFromFileLoader;
	const float m_spacingBetweenWidgets;
	static sfg::Box::Ptr m_scrolledWindowBox;
};
