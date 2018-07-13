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

	static BlockTypes& GetCurrentBlock();
	static sf::RectangleShape& GetMouseHighlight();
	static std::vector< std::vector<int> >& GetTilesContainer();

private:
	std::vector<int> GetTileAtGivenCoords(int, int) const;
	void HighlightTile();
	void DrawAllTiles();
	bool CheckIfAnyTilePositionMatchesGivenCoords(int x, int y) const;
	static void InitMouseHighlight();

private:
	sf::RenderWindow* m_ptrMainWindow;
	sf::Sprite m_spriteForDrawing;
	TextureManager m_textures;
	static BlockTypes m_currentBlock;
	static std::vector< std::vector<int> >m_tilesInfoContainer;
	static sf::RectangleShape m_mouseHighlight;
};
