#pragma once

#include <SFML\Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Interface.h"
#include "Camera.h"

class MainWindow
{
public:
	MainWindow(int , int);
	void RunMainLoop();
	void Input(float delta_time);
	void Update();
	void Render();

private:
	void HandleWindowEvents();
	void IfUserClickedTile();
	bool IfUserAddsTile();
	bool IfUserDeletsTile();

private:
	sf::RenderWindow m_mainWindow;
	sfg::SFGUI m_sfgui;
	sf::Color m_backgroundColor;
	sf::Clock m_deltaTimer;
	Interface m_interface;
	Camera m_camera;
};