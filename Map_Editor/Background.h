#pragma once

#include <SFML/Graphics.hpp>

class Background
{
public:
	Background(sf::RenderWindow&);
	void Draw(sf::RenderWindow&);
	void Update(const sf::RenderWindow&);
private:
	void CreateNet();
	void SetupGradient(const sf::RenderWindow&);
	void UpdateGradient(const sf::RenderWindow&);
private:
	sf::VertexArray m_verticalLines;
	sf::VertexArray m_horizontalLines;
	sf::VertexArray m_gradient;
	const float m_fixedTileSize;
};