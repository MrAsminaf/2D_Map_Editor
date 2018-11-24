#pragma once

#include "Resource_Managment/BlockTypes.h"
#include "Resource_Managment/TextureManager.h"
#include "Layout.h"
#include <vector>
#include <iostream>


// A struct that represents a block in foreground; stored in static foregroundBlocks 
struct Block
{
	int x;
	int y;
	BlockTypes blockType;
};

class Foreground
{
public:
	Foreground(sf::RenderWindow& mainWindow);
	void DeleteTile();
	void AddTile();
	void Draw();
	void Update();
	static sf::RectangleShape& GetMouseHighlight();
	static BlockTypes& GetCurrentBlock();
	static bool CheckIfTileExists(const int x, const int y, const Mode mode);
	static std::vector<Block>& GetTilesContainer(const Mode m);
	static Block GetTileAtCoords(const int x, const int y, const Mode mode);
private:
	virtual void HighlightTile();
	void InitMouseHighlight();
	void DrawTiles();
private:
	// Pointer to main window, used when obtaining mouse pos and drawing
	sf::RenderWindow* m_mainWindowPtr;

	// Sprite used to draw each block in foreground
	sf::Sprite m_spriteForDrawing;

	// Object used when assigning textures to each block
	TextureManager m_textures;

	// Static vectors that hold every foreground and background entity
	static std::vector<Block>foregroundBlocks;
	static std::vector<Block>backgroundBlocks;

	// A "highlighter" used to show at which block the mouse is pointing currently
	static sf::RectangleShape mouseHighlight;

	// An object that holds information about which block is currently used
	static BlockTypes currentBlock;
};