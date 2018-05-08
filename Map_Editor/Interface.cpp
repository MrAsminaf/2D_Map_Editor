#include "Interface.h"

Interface::Interface(sf::RenderWindow& main_window)
	:
	m_ptrMainWindow(&main_window),
	m_gradient(sf::Quads, 4),
	m_gui(m_mousePointingHighlight, m_currentChosenBlock, m_tilesToDrawInfoContainer),
	m_verticalLines(sf::Lines, 2000),
	m_horizontalLines(sf::Lines, 2000)
{
	m_currentChosenBlock = TextureLoader::ID::ENUM_NONE;
	m_mousePointingHighlight.setFillColor(sf::Color(60, 60, 60, 150));
	m_mousePointingHighlight.setSize(sf::Vector2f(m_fixedTileSize, m_fixedTileSize));

	SetupGradient();
	CreateNet();
}

void Interface::Draw()
{
	m_ptrMainWindow->draw(m_gradient);
	DrawNet();
	m_ptrMainWindow->draw(m_mousePointingHighlight);
	DrawAllTiles();
}

void Interface::HandleSFGUIEvents(sf::Event event)
{
	m_gui.HandleEvents(event);
}

void Interface::Update()
{
	UpdateGradient();
	m_gui.Update();
	HighlightTile();
}

void Interface::AddTile()
{
	int placedBlockId = m_currentChosenBlock;

	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_ptrMainWindow);
	int x = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).x / 16));
	int y = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).y / 16));

	if (x >= 0 && y >= 0 && sf::Mouse::getPosition(*m_ptrMainWindow).x > 140)
	{
		if (!CheckIfAnyTilePositionMatchesGivenCoords(x, y))
		{
			std::vector<int> clickedTileInfo;
			clickedTileInfo.push_back(x);
			clickedTileInfo.push_back(y);
			clickedTileInfo.push_back(placedBlockId);

			m_tilesToDrawInfoContainer.push_back(clickedTileInfo);
			std::cout << "Added. Current size: " << m_tilesToDrawInfoContainer.size() << std::endl;
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

	for (auto it = m_tilesToDrawInfoContainer.cbegin(); it != m_tilesToDrawInfoContainer.cend(); ++it)
	{
		if ((*it)[xCoordOfDeletedTile] == x && (*it)[yCoordOfDeletedTile] == y)
		{
			m_tilesToDrawInfoContainer.erase(it);
			std::cout << "Erased. Current size: " << m_tilesToDrawInfoContainer.size() << std::endl;
			return;
		}
	}
}

sf::Vector2f Interface::ScaleMousePosToTileSize()
{
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(*m_ptrMainWindow);
	//int clickedTileXCoord = (int(main_window.mapPixelToCoords(currentMousePos).x / m_fixedTileSize));
	//int clickedTileYCoord = (int(main_window.mapPixelToCoords(currentMousePos).y / m_fixedTileSize));
	//sf::Vector2f mappedPosToCoords(clickedTileXCoord, clickedTileYCoord);

	sf::Vector2f mappedPosToCoords = m_ptrMainWindow->mapPixelToCoords(currentMousePos);

	return mappedPosToCoords;
}

void Interface::CreateNet()
{
	int verticalVertexIndex = 0;
	for (int i = 0; i < 400; ++i)
	{
		sf::Vertex* singleLine = &m_verticalLines[verticalVertexIndex];
		singleLine->position = sf::Vector2f(i*m_fixedTileSize, 0);
		singleLine->color = sf::Color(64, 64, 64);
		(singleLine + 1)->position = sf::Vector2f(i*m_fixedTileSize, 1904);
		(singleLine + 1)->color = sf::Color(64, 64, 64);
		verticalVertexIndex += 2;
	}

	int horizontalVertexIndex = 0;
	for (int i = 0; i < 120; ++i)
	{
		sf::Vertex* singleLine = &m_horizontalLines[horizontalVertexIndex];
		singleLine->position = sf::Vector2f(0, i*m_fixedTileSize);
		singleLine->color = sf::Color(64, 64, 64);
		(singleLine + 1)->position = sf::Vector2f(6400, i*m_fixedTileSize);
		(singleLine + 1)->color = sf::Color(64, 64, 64);
		horizontalVertexIndex += 2;
	}
}

void Interface::SetupGradient()
{
	m_gradient[0].position = sf::Vector2f(0, 0);
	m_gradient[1].position = sf::Vector2f(float(m_ptrMainWindow->getSize().x), 0);
	m_gradient[2].position = sf::Vector2f(float(m_ptrMainWindow->getSize().x), float(m_ptrMainWindow->getSize().y));
	m_gradient[3].position = sf::Vector2f(0, float(m_ptrMainWindow->getSize().y));

	m_gradient[0].color = sf::Color(40, 40, 40);
	m_gradient[1].color = sf::Color(40, 40, 40);
	m_gradient[2].color = sf::Color(30, 30, 30);
	m_gradient[3].color = sf::Color(30, 30, 30);
}

void Interface::UpdateGradient()
{
	m_gradient[0].position = sf::Vector2f(m_ptrMainWindow->mapPixelToCoords(sf::Vector2i(0, 0)));
	m_gradient[1].position = sf::Vector2f(m_ptrMainWindow->mapPixelToCoords(sf::Vector2i(m_ptrMainWindow->getSize().x, 0)));
	m_gradient[2].position = sf::Vector2f(m_ptrMainWindow->mapPixelToCoords(sf::Vector2i(m_ptrMainWindow->getSize().x, m_ptrMainWindow->getSize().y)));
	m_gradient[3].position = sf::Vector2f(m_ptrMainWindow->mapPixelToCoords(sf::Vector2i(0, m_ptrMainWindow->getSize().y)));
}

void Interface::DrawNet()
{ 
	m_ptrMainWindow->draw(m_verticalLines);
	m_ptrMainWindow->draw(m_horizontalLines);
}

void Interface::HighlightTile()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_ptrMainWindow);
	int x = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).x / 16));
	int y = (int(m_ptrMainWindow->mapPixelToCoords(mousePos).y / 16));

	x *= 16;
	y *= 16;

	m_mousePointingHighlight.setPosition(float(x), float(y));
}

void Interface::DrawAllTiles()
{
	const int tile_x_coord = 0;
	const int tile_y_coord = 1;
	const int tile_texture_id = 2;

	for (auto it = m_tilesToDrawInfoContainer.begin(); it != m_tilesToDrawInfoContainer.end(); ++it)
	{
		m_grassSprite.setPosition(float((*it)[tile_x_coord] * m_fixedTileSize), float((*it)[tile_y_coord] * m_fixedTileSize));

		switch ((*it)[tile_texture_id])
		{
		case TextureLoader::ID::ENUM_GRASS:
			m_grassSprite.setTexture(m_textures.GetTextureById(TextureLoader::ENUM_GRASS));
			break;

		case TextureLoader::ID::ENUM_DIRT:
			m_grassSprite.setTexture(m_textures.GetTextureById(TextureLoader::ENUM_DIRT));
			break;

		case TextureLoader::ID::ENUM_GRASS_ULDR:
			m_grassSprite.setTexture(m_textures.GetTextureById(TextureLoader::ENUM_GRASS_ULDR));
			break;

		case TextureLoader::ID::ENUM_GRASS_DLTR:
			m_grassSprite.setTexture(m_textures.GetTextureById(TextureLoader::ENUM_GRASS_DLTR));
			break;

		case TextureLoader::ID::ENUM_STONE:
			m_grassSprite.setTexture(m_textures.GetTextureById(TextureLoader::ENUM_STONE));
			break;

		case TextureLoader::ENUM_DIRT_DLTR:
			m_grassSprite.setTexture(m_textures.GetTextureById(TextureLoader::ENUM_DIRT_DLTR));
			break;

		case TextureLoader::ENUM_DIRT_TLDR:
			m_grassSprite.setTexture(m_textures.GetTextureById(TextureLoader::ENUM_DIRT_TLDR));
			break;

		default:
			break;
		}
		m_ptrMainWindow->draw(m_grassSprite);
	}
}

bool Interface::CheckIfAnyTilePositionMatchesGivenCoords(int x_coord, int y_coord)
{
	for (auto it : m_tilesToDrawInfoContainer)
	{
		if (it[0] == x_coord && it[1] == y_coord)
			return true;
	}
	return false;
}

std::vector<int> Interface::GetTileAtGivenCoords(int x, int y)
{
	for (auto it : m_tilesToDrawInfoContainer)
	{
		if (it[0] == x && it[1] == y)
			return it;
	}
}

TextureLoader::ID Interface::GetCurrentChosenBlock() const
{
	return m_currentChosenBlock;
}
