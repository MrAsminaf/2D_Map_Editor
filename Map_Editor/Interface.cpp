#include "Interface.h"

Interface::Interface(sf::RenderWindow& main_window)
	:
	m_ptrMainWindow(&main_window),
	m_currentBlock(BlockTypes::ENUM_NONE)
{
	m_mouseHighlight.setFillColor(sf::Color(60, 60, 60, 150));
	m_mouseHighlight.setSize(sf::Vector2f(16, 16));
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

	int xCoordOfDeletedTile = 0; // for readability in loop
	int yCoordOfDeletedTile = 1; // for readability in loop

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
	const int tile_x_coord = 0;
	const int tile_y_coord = 1;
	const int tile_texture_id = 2;

	for (auto& it : m_tilesInfoContainer)
	{
		m_spriteForDrawing.setPosition(float(it[tile_x_coord] * 16), float(it[tile_y_coord] * 16));

		switch (it[tile_texture_id])
		{
		case BlockTypes::ENUM_GRASS:
			m_spriteForDrawing.setTexture(m_textures.GetTextureById(BlockTypes::ENUM_GRASS));
			break;

		case BlockTypes::ENUM_DIRT:
			m_spriteForDrawing.setTexture(m_textures.GetTextureById(BlockTypes::ENUM_DIRT));
			break;

		case BlockTypes::ENUM_GRASS_ULDR:
			m_spriteForDrawing.setTexture(m_textures.GetTextureById(BlockTypes::ENUM_GRASS_ULDR));
			break;

		case BlockTypes::ENUM_GRASS_DLTR:
			m_spriteForDrawing.setTexture(m_textures.GetTextureById(BlockTypes::ENUM_GRASS_DLTR));
			break;

		case BlockTypes::ENUM_STONE:
			m_spriteForDrawing.setTexture(m_textures.GetTextureById(BlockTypes::ENUM_STONE));
			break;

		case BlockTypes::ENUM_DIRT_DLTR:
			m_spriteForDrawing.setTexture(m_textures.GetTextureById(BlockTypes::ENUM_DIRT_DLTR));
			break;

		case BlockTypes::ENUM_DIRT_TLDR:
			m_spriteForDrawing.setTexture(m_textures.GetTextureById(BlockTypes::ENUM_DIRT_TLDR));
			break;

		default:
			break;
		}
		m_ptrMainWindow->draw(m_spriteForDrawing);
	}
}

bool Interface::CheckIfAnyTilePositionMatchesGivenCoords(int x_coord, int y_coord) const
{
	for (auto& it : m_tilesInfoContainer)
	{
		if (it[0] == x_coord && it[1] == y_coord)
			return true;
	}
	return false;
}

std::vector<int> Interface::GetTileAtGivenCoords(int x, int y) const
{
	for (auto& it : m_tilesInfoContainer)
	{
		if (it[0] == x && it[1] == y)
			return it;
	}
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
