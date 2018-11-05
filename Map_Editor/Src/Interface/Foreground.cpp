#include "Foreground.h"

// --- Static members initialization --- //
std::vector<Block> Foreground::foregroundBlocks;
std::vector<Block> Foreground::backgroundBlocks;
BlockTypes Foreground::currentBlock = BlockTypes::ENUM_NONE;
sf::RectangleShape Foreground::mouseHighlight;

void Foreground::Draw()
{
	DrawTiles();
	m_mainWindowPtr->draw(mouseHighlight);
}

void Foreground::Update()
{
	HighlightTile();
}

sf::RectangleShape & Foreground::GetMouseHighlight()
{
	return mouseHighlight;
}

BlockTypes & Foreground::GetCurrentBlock()
{
	return currentBlock;
}

// Used to update position of a highlighter
void Foreground::HighlightTile()
{
	auto mousePos = sf::Mouse::getPosition(*m_mainWindowPtr);

	if (Layout::GetMode() == Mode::FOREGROUND)
	{
		int x = (int (m_mainWindowPtr->mapPixelToCoords(mousePos).x / 16) );
		int y = (int (m_mainWindowPtr->mapPixelToCoords(mousePos).y / 16) );

		x *= 16;
		y *= 16;

		mouseHighlight.setPosition(float(x), float(y));
	}
	else
	{
		int x = (int (m_mainWindowPtr->mapPixelToCoords(mousePos).x / 16) );
		int y = (int ((m_mainWindowPtr->mapPixelToCoords(mousePos).y + 8) / 16) );

		x = x * 16;
		y = y * 16 - 8;

		mouseHighlight.setPosition(float(x), float(y));
	}
}

bool Foreground::CheckIfTileExists(const int x, const int y, const Mode mode)
{
	for (const auto& block : ((mode == Mode::FOREGROUND)? foregroundBlocks : backgroundBlocks) )
	{
		if (block.x == x && block.y == y)
			return true;
	}
	return false;
}

void Foreground::InitMouseHighlight()
{
	mouseHighlight.setFillColor(sf::Color(60, 60, 60, 150));
	mouseHighlight.setSize(sf::Vector2f(16, 16));
}

void Foreground::DrawTiles()
{
	for (auto& tile : backgroundBlocks)
	{
		m_spriteForDrawing.setPosition(float(tile.x * 16), float(tile.y * 16 - 8));
		m_spriteForDrawing.setTexture(m_textures.GetTextureById(tile.blockType), true);
		m_mainWindowPtr->draw(m_spriteForDrawing);
	}

	for (auto& tile : foregroundBlocks)
	{
		m_spriteForDrawing.setPosition(float(tile.x * 16), float(tile.y * 16));
		m_spriteForDrawing.setTexture(m_textures.GetTextureById(tile.blockType), true);
		m_mainWindowPtr->draw(m_spriteForDrawing);
	}
}

std::vector<Block>& Foreground::GetTilesContainer()
{
	return foregroundBlocks;
}

Foreground::Foreground(sf::RenderWindow& mainWindow)
	:
	m_mainWindowPtr(&mainWindow)
{
	InitMouseHighlight();
}

void Foreground::DeleteTile()
{
	auto mousePos = sf::Mouse::getPosition(*m_mainWindowPtr);

	if (Layout::GetMode() == Mode::FOREGROUND)
	{
		int x = (int(m_mainWindowPtr->mapPixelToCoords(mousePos).x / 16));
		int y = (int(m_mainWindowPtr->mapPixelToCoords(mousePos).y / 16));

		for (auto it = foregroundBlocks.cbegin(); it != foregroundBlocks.cend(); ++it)
		{
			if ((*it).x == x && (*it).y == y)
			{
				foregroundBlocks.erase(it);
				std::cout << "Erased. Current size: " << foregroundBlocks.size() << std::endl;
				return;
			}
		}
	}
	else
	{
		int x = (int(m_mainWindowPtr->mapPixelToCoords(mousePos).x / 16));
		int y = (int((m_mainWindowPtr->mapPixelToCoords(mousePos).y + 8) / 16));

		for (auto it = backgroundBlocks.cbegin(); it != backgroundBlocks.cend(); ++it)
		{
			if ((*it).x == x && (*it).y == y)
			{
				backgroundBlocks.erase(it);
				std::cout << "Erased. Current size: " << backgroundBlocks.size() << std::endl;
				return;
			}
		}
	}
}

void Foreground::AddTile()
{
	auto mousePos = sf::Mouse::getPosition(*m_mainWindowPtr);

	if (Layout::GetMode() == Mode::FOREGROUND)
	{
		int x = (int(m_mainWindowPtr->mapPixelToCoords(mousePos).x / 16));
		int y = (int(m_mainWindowPtr->mapPixelToCoords(mousePos).y / 16));

		if (x >= 0 && y >= 0 && sf::Mouse::getPosition(*m_mainWindowPtr).x > 140 && x < 400 && y < 119)
		{
			if (!CheckIfTileExists(x, y, Mode::FOREGROUND))
			{
				Block tempBlock;
				tempBlock.x = x;
				tempBlock.y = y;
				tempBlock.blockType = currentBlock;
				foregroundBlocks.push_back(tempBlock);
				std::cout << "Added to foreground. Current size: " << foregroundBlocks.size() << std::endl;
			}
		}
	}
	else
	{
		int x = (int(m_mainWindowPtr->mapPixelToCoords(mousePos).x / 16));
		int y = (int((m_mainWindowPtr->mapPixelToCoords(mousePos).y + 8) / 16));

		if (x >= 0 && y >= 0 && sf::Mouse::getPosition(*m_mainWindowPtr).x > 140 && x < 400 && y < 119)
		{
			if (!CheckIfTileExists(x, y, Mode::BACKGROUND))
			{
				Block tempBlock;
				tempBlock.x = x;
				tempBlock.y = y;
				tempBlock.blockType = currentBlock;
				backgroundBlocks.push_back(tempBlock);
				std::cout << "Added to background. Current size: " << backgroundBlocks.size() << std::endl;
			}
		}
	}
}

Block Foreground::GetTileAtCoords(const int x, const int y, const Mode mode)
{
	for (auto& it : ((mode == Mode::FOREGROUND) ? foregroundBlocks : backgroundBlocks))
	{
		if (it.x == x && it.y == y)
			return it;
	}
}
