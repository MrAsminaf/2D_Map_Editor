#include "Layout.h"

sf::Color Layout::m_gradientColor(40, 40, 40);
sf::Color Layout::m_netColor(64, 64, 64);
Mode Layout::m_currentMode(Mode::FOREGROUND);

Layout::Layout(sf::RenderWindow& rWindow)
	:
	m_foregroundVerticalLines(sf::Lines, 2000),
	m_foregroundHorizontalLines(sf::Lines, 2000),
	m_backgroundVerticalLines(sf::Lines, 2000),
	m_backgroundHorizontalLines(sf::Lines, 2000),
	m_gradient(sf::Quads, 4),
	m_fixedTileSize(16)
{
	SetupGradient(rWindow);
	CreateForegroundNet();
}

void Layout::Draw(sf::RenderWindow & mainWindow)
{
	mainWindow.draw(m_gradient);
	if (m_currentMode == Mode::FOREGROUND)
	{
		mainWindow.draw(m_foregroundVerticalLines);
		mainWindow.draw(m_foregroundHorizontalLines);
	}
	else
	{
		mainWindow.draw(m_backgroundVerticalLines);
		mainWindow.draw(m_backgroundHorizontalLines);
	}
}

void Layout::Update(const sf::RenderWindow & mainWindow)
{
	UpdateGradient(mainWindow);
}

void Layout::SetMode(const Mode mode)
{
	m_currentMode = mode;
}

Mode Layout::GetMode()
{
	return m_currentMode;
}

void Layout::CreateForegroundNet()
{
	int index = 0;
	for (int i = 0; i < 400; ++i)
	{
		sf::Vertex* singleForegroundLine = &m_foregroundVerticalLines[index];
		sf::Vertex* singleBackgroundLine = &m_backgroundVerticalLines[index];

		singleForegroundLine->position = sf::Vector2f(i * m_fixedTileSize, 0);
		singleBackgroundLine->position = sf::Vector2f(i * m_fixedTileSize, -m_fixedTileSize / 2);

		singleForegroundLine->color = m_netColor;
		singleBackgroundLine->color = m_netColor;

		(singleForegroundLine + 1)->position = sf::Vector2f(i * m_fixedTileSize, 1904);
		(singleBackgroundLine + 1)->position = sf::Vector2f(i * m_fixedTileSize, 1904 - (m_fixedTileSize / 2));

		(singleForegroundLine + 1)->color = m_netColor;
		(singleBackgroundLine + 1)->color = m_netColor;

		index += 2;
	}

	index = 0;
	for (int i = 0; i < 120; ++i)
	{
		sf::Vertex* singleForegroundLine = &m_foregroundHorizontalLines[index];
		sf::Vertex* singleBackgroundLine = &m_backgroundHorizontalLines[index];

		singleForegroundLine->position = sf::Vector2f(0, i * m_fixedTileSize);
		singleBackgroundLine->position = sf::Vector2f(0, i*m_fixedTileSize - (m_fixedTileSize / 2));

		singleForegroundLine->color = m_netColor;
		singleBackgroundLine->color = m_netColor;

		(singleForegroundLine + 1)->position = sf::Vector2f(6400, i * m_fixedTileSize);
		(singleBackgroundLine + 1)->position = sf::Vector2f(6400, i * m_fixedTileSize - (m_fixedTileSize / 2));

		(singleForegroundLine + 1)->color = m_netColor;
		(singleBackgroundLine + 1)->color = m_netColor;

		index += 2;
	}
}

void Layout::CreateBackgroundNet()
{
	int verticalVertexIndex = 0;
	for (int i = 0; i < 400; ++i)
	{
		sf::Vertex* singleLine = &m_foregroundVerticalLines[verticalVertexIndex];
		singleLine->position = sf::Vector2f(i * m_fixedTileSize, 0);
		singleLine->color = m_netColor;
		(singleLine + 1)->position = sf::Vector2f(i * m_fixedTileSize, 1904);
		(singleLine + 1)->color = m_netColor;
		verticalVertexIndex += 2;
	}

	int horizontalVertexIndex = 0;
	for (int i = 0; i < 120; ++i)
	{
		sf::Vertex* singleLine = &m_foregroundHorizontalLines[horizontalVertexIndex];
		singleLine->position = sf::Vector2f(0, i * m_fixedTileSize);
		singleLine->color = m_netColor;
		(singleLine + 1)->position = sf::Vector2f(6400, i * m_fixedTileSize);
		(singleLine + 1)->color = m_netColor;
		horizontalVertexIndex += 2;
	}
}

void Layout::SetupGradient(const sf::RenderWindow & mainWindow)
{
	m_gradient[0].position = sf::Vector2f(0, 0);
	m_gradient[1].position = sf::Vector2f(float(mainWindow.getSize().x), 0);
	m_gradient[2].position = sf::Vector2f(float(mainWindow.getSize().x), float(mainWindow.getSize().y));
	m_gradient[3].position = sf::Vector2f(0, float(mainWindow.getSize().y));

	m_gradient[0].color = m_gradientColor;
	m_gradient[1].color = m_gradientColor;
	m_gradient[2].color = m_gradientColor;
	m_gradient[3].color = m_gradientColor;
}

void Layout::UpdateGradient(const sf::RenderWindow & mainWindow)
{
	m_gradient[0].position = sf::Vector2f(mainWindow.mapPixelToCoords(sf::Vector2i(0, 0)));
	m_gradient[1].position = sf::Vector2f(mainWindow.mapPixelToCoords(sf::Vector2i(mainWindow.getSize().x, 0)));
	m_gradient[2].position = sf::Vector2f(mainWindow.mapPixelToCoords(sf::Vector2i(mainWindow.getSize().x, mainWindow.getSize().y)));
	m_gradient[3].position = sf::Vector2f(mainWindow.mapPixelToCoords(sf::Vector2i(0, mainWindow.getSize().y)));

	m_gradient[0].color = m_gradientColor;
	m_gradient[1].color = m_gradientColor;
	m_gradient[2].color = m_gradientColor;
	m_gradient[3].color = m_gradientColor;

	for (int i = 0; i < 800; ++i)
	{
		m_foregroundVerticalLines[i].color = m_netColor;
		m_backgroundVerticalLines[i].color = m_netColor;
		if (i <= 240)
		{
			m_foregroundHorizontalLines[i].color = m_netColor;
			m_backgroundHorizontalLines[i].color = m_netColor;
		}
	}

}
