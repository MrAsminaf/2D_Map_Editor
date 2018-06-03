#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <string>

#include "TextureManager.h"

class Interface
{
public:
	Interface(sf::RenderWindow& main_window);
	void Draw();
	void Update();
	void AddTile();
	void DeleteTile();

	//Getters
	BlockTypes& GetCurrentBlock();
	sf::RectangleShape& GetMouseHighlight();
	std::vector< std::vector<int> >& GetTilesContainer();

private:
	void HighlightTile();
	void DrawAllTiles();
	bool CheckIfAnyTilePositionMatchesGivenCoords(int x, int y) const;
	std::vector<int> GetTileAtGivenCoords(int, int) const;

private:
	sf::RenderWindow* m_ptrMainWindow;
	sf::RectangleShape m_mouseHighlight;
	sf::Sprite m_spriteForDrawing;
	std::vector< std::vector<int> >m_tilesInfoContainer;
	TextureManager m_textures;
	BlockTypes m_currentBlock;
};
