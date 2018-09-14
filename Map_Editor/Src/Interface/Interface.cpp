#include "Interface.h"

BlockTypes Interface::m_currentBlock = BlockTypes::ENUM_NONE;
sf::RectangleShape Interface::m_mouseHighlight;
std::vector< std::vector<int> >Interface::m_tilesInfoContainer;

Interface::Interface(sf::RenderWindow& main_window)
	:
	m_ptrMainWindow(&main_window)
{
	InitMouseHighlight();
}

void Interface::Draw()
{
	m_ptrMainWindow->draw(m_mouseHighlight);
	DrawAllTiles();
}

void Interface::Update()
{
	HighlightTile();
}

void Interface::AddTile()
{
	const int placedBlockId = m_currentBlock;

	auto mousePos = sf::Mouse::getPosition(*m_ptrMainWindow);
	int x = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).x / 16));
	int y = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).y / 16));

	if (x >= 0 && y >= 0 && sf::Mouse::getPosition(*m_ptrMainWindow).x > 140 && x < 400 && y < 119)
	{
		if (!CheckIfAnyTilePositionMatchesGivenCoords(x, y))
		{
			std::vector<int> clickedTileInfo;
			clickedTileInfo.push_back(x);
			clickedTileInfo.push_back(y);
			clickedTileInfo.push_back(placedBlockId);

			m_tilesInfoContainer.push_back(clickedTileInfo);
			std::cout << "Added. Current size: " << m_tilesInfoContainer.size() << std::endl;
		}
	}
}

void Interface::DeleteTile()
{
	auto mousePos = sf::Mouse::getPosition(*m_ptrMainWindow);
	int x = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).x / 16));
	int y = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).y / 16));

	int xCoordOfDeletedTile = 0;
	int yCoordOfDeletedTile = 1;

	for (auto it = m_tilesInfoContainer.cbegin(); it != m_tilesInfoContainer.cend(); ++it)
	{
		if ((*it)[xCoordOfDeletedTile] == x && (*it)[yCoordOfDeletedTile] == y)
		{
			m_tilesInfoContainer.erase(it);
			std::cout << "Erased. Current size: " << m_tilesInfoContainer.size() << std::endl;
			return;
		}
	}
}


void Interface::HighlightTile()
{
	auto mousePos = sf::Mouse::getPosition(*m_ptrMainWindow);
	int x = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).x / 16));
	int y = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).y / 16));

	x *= 16;
	y *= 16;

	m_mouseHighlight.setPosition(float(x), float(y));
}

void Interface::DrawAllTiles()
{
	constexpr int X = 0;
	constexpr int Y = 1;
	constexpr int ID = 2;
	constexpr int TILE_SIZE = 16;

	for (auto& tile : m_tilesInfoContainer)
	{
		m_spriteForDrawing.setPosition(float(tile[X] * TILE_SIZE), float(tile[Y] * TILE_SIZE));
		m_spriteForDrawing.setTexture(m_textures.GetTextureById(tile[ID]));
		m_ptrMainWindow->draw(m_spriteForDrawing);
	}
}

bool Interface::CheckIfAnyTilePositionMatchesGivenCoords(int x, int y) const
{
	constexpr int X = 0, Y = 1;

	for (auto& it : m_tilesInfoContainer)
	{
		if (it[X] == x && it[Y] == y)
			return true;
	}
	return false;
}

std::vector<int> Interface::GetTileAtGivenCoords(int x, int y) const
{
	constexpr int X = 0, Y = 1;

	for (auto& it : m_tilesInfoContainer)
	{
		if (it[X] == x && it[Y] == y)
			return it;
	}
}

void Interface::InitMouseHighlight()
{
	m_mouseHighlight.setFillColor(sf::Color(60, 60, 60, 150));
	m_mouseHighlight.setSize(sf::Vector2f(16, 16));
}

BlockTypes& Interface::GetCurrentBlock()
{
	return m_currentBlock;
}

sf::RectangleShape& Interface::GetMouseHighlight()
{
	return m_mouseHighlight;
}

std::vector<std::vector<int>>& Interface::GetTilesContainer()
{
	return m_tilesInfoContainer;
}
