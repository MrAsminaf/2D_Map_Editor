#pragma once

#include <SFML\Graphics.hpp>

#include <Windows.h>

class Camera
{
public:
	Camera(sf::RenderWindow& window);
	void Update(sf::RenderWindow& main_window);
	void Move(float delta_time);
	void ZoomIn();
	void ZoomOut();
	sf::View GetView() const;
	sf::Vector2f GetCenter() const;

private:
	sf::View m_view;
	const float m_cameraSpeed = 500.0f;
};