#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "TextureLoader.h"
#include "GUI.h"
#include "MapFileGenerator.h"

class Interface
{
public:
	Interface(sf::RenderWindow& main_window);
	void Draw();
	void Update();
	void HandleSFGUIEvents(sf::Event event);
	void AddTile();
	void DeleteTile();
	void DrawAllTiles();
	void DrawNet();
	TextureLoader::ID GetCurrentChosenBlock()const;

private:
	sf::Vector2f ScaleMousePosToTileSize(); //Fix this crap (someday)
	void CreateNet();
	void SetupGradient();
	void UpdateGradient();
	void HighlightTile();
	bool CheckIfAnyTilePositionMatchesGivenCoords(int x, int y);
	std::vector<int> GetTileAtGivenCoords(int, int);


private:
	sf::RenderWindow* m_ptrMainWindow;
	sf::RectangleShape m_mousePointingHighlight;
	sf::Sprite m_grassSprite;
	sf::VertexArray m_gradient;
	std::vector< std::vector<int> >m_tilesToDrawInfoContainer;
	TextureLoader m_textures;
	TextureLoader::ID m_currentChosenBlock;
	MapFileGenerator m_mapFileGenerator;
	GUI m_gui;
	const float m_fixedTileSize = 16.0f;
	sf::VertexArray m_verticalLines;
	sf::VertexArray m_horizontalLines;
};
