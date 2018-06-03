#include "Camera.h"

Camera::Camera(const sf::RenderWindow& window)
	:
	m_cameraSpeed(500.0f)
{
	m_view.setSize(sf::Vector2f(window.getSize()));
	m_view.setCenter(400, 300);
}

void Camera::UpdateMainWindowView(sf::RenderWindow& main_window)
{
	main_window.setView(m_view);
}

void Camera::Move(float delta_time)
{
	float currSpeed = m_cameraSpeed * delta_time;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_view.move(currSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_view.move(-currSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_view.move(0, -currSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_view.move(0, currSpeed);
}

sf::View Camera::GetView() const
{
	return m_view;
}

sf::Vector2f Camera::GetCenter() const
{
	return m_view.getCenter();
}

void Camera::ZoomIn()
{
	m_view.zoom(0.8f);
}

void Camera::ZoomOut()
{
	m_view.zoom(1.1f);
}
