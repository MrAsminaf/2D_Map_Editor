#pragma once

#include <SFML/Graphics.hpp>

enum Mode
{
	FOREGROUND,
	BACKGROUND
};

class Layout
{
public:
	Layout(sf::RenderWindow&);
	void Draw(sf::RenderWindow&);
	void Update(const sf::RenderWindow&);
	static void SetMode(const Mode mode);
private:
	void CreateForegroundNet();
	void CreateBackgroundNet();
	void SetupGradient(const sf::RenderWindow&);
	void UpdateGradient(const sf::RenderWindow&);
public:
	static sf::Color m_gradientColor;
	static sf::Color m_netColor;
private:
	sf::VertexArray m_foregroundVerticalLines;
	sf::VertexArray m_foregroundHorizontalLines;
	sf::VertexArray m_backgroundVerticalLines;
	sf::VertexArray m_backgroundHorizontalLines;
	sf::VertexArray m_gradient;
	const float m_fixedTileSize;
	static Mode m_currentMode;
};