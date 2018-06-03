#include "Background.h"

Background::Background(sf::RenderWindow& rWindow)
	:
	m_verticalLines(sf::Lines, 2000),
	m_horizontalLines(sf::Lines, 2000),
	m_gradient(sf::Quads, 4),
	m_fixedTileSize(16)
{
	SetupGradient(rWindow);
	CreateNet();
}

void Background::Draw(sf::RenderWindow & rWindow)
{
	rWindow.draw(m_gradient);
	rWindow.draw(m_verticalLines);
	rWindow.draw(m_horizontalLines);
}

void Background::Update(const sf::RenderWindow & rWindow)
{
	UpdateGradient(rWindow);
}

void Background::CreateNet()
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

void Background::SetupGradient(const sf::RenderWindow & rWindow)
{
	m_gradient[0].position = sf::Vector2f(0, 0);
	m_gradient[1].position = sf::Vector2f(float(rWindow.getSize().x), 0);
	m_gradient[2].position = sf::Vector2f(float(rWindow.getSize().x), float(rWindow.getSize().y));
	m_gradient[3].position = sf::Vector2f(0, float(rWindow.getSize().y));

	m_gradient[0].color = sf::Color(40, 40, 40);
	m_gradient[1].color = sf::Color(40, 40, 40);
	m_gradient[2].color = sf::Color(30, 30, 30);
	m_gradient[3].color = sf::Color(30, 30, 30);
}

void Background::UpdateGradient(const sf::RenderWindow & rWindow)
{
	m_gradient[0].position = sf::Vector2f(rWindow.mapPixelToCoords(sf::Vector2i(0, 0)));
	m_gradient[1].position = sf::Vector2f(rWindow.mapPixelToCoords(sf::Vector2i(rWindow.getSize().x, 0)));
	m_gradient[2].position = sf::Vector2f(rWindow.mapPixelToCoords(sf::Vector2i(rWindow.getSize().x, rWindow.getSize().y)));
	m_gradient[3].position = sf::Vector2f(rWindow.mapPixelToCoords(sf::Vector2i(0, rWindow.getSize().y)));
}
