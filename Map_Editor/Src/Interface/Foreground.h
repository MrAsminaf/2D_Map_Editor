#pragma once

// --- Base class: --- //
#include "Interaface.h"

// --- Other --- //
#include "Resource_Managment/BlockTypes.h"
#include "Resource_Managment/TextureManager.h"
#include <vector>
#include <iostream>


// A struct that represents a block in foreground; stored in static foregroundBlocks 
struct ForegroundBlock
{
	int x;
	int y;
	BlockTypes blockType;
};

class Foreground : public Interface<ForegroundBlock>
{
public:
	Foreground(sf::RenderWindow& mainWindow);
	virtual void DeleteTile() override;
	virtual void AddTile() override;
	virtual ForegroundBlock GetTileAtCoords(int x, int y) override;
	static std::vector<ForegroundBlock>& GetTilesContainer();
	void Draw();
	void Update();
	static sf::RectangleShape& GetMouseHighlight();
	static BlockTypes& GetCurrentBlock();
private:
	virtual void HighlightTile() override;
	virtual bool CheckIfTileExists(int x, int y) const override;
	void InitMouseHighlight();
	void DrawTiles();
private:
	// Pointer to main window, used when obtaining mouse pos and drawing
	sf::RenderWindow* m_mainWindowPtr;

	// Sprite used to draw each block in foreground
	sf::Sprite m_spriteForDrawing;

	// Object used when assigning textures to each block
	TextureManager m_textures;

	// Static vector that holds every foreground entity
	static std::vector<ForegroundBlock>foregroundBlocks;

	// A "highlighter" used to show at which block the mouse is pointing currently
	static sf::RectangleShape mouseHighlight;

	// An object that holds information about which block is currently used
	static BlockTypes currentBlock;
};