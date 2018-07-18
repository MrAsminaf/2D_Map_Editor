#pragma once

#include "imgui.h"
#include "imgui-sfml-master/imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Camera.h"
#include "Background.h"
#include "GUI.h"

class MainWindow
{
public:
	MainWindow();
	~MainWindow();
	MainWindow(int , int);
	void RunMainLoop();
	void Input(float delta_time);
	void Update();
	void Render();

private:
	void HandleWindowEvents();
	void IfUserClickedTile();
	bool IfUserAddsTile();
	bool IfUserDeletsTile() const;

private:
	sf::RenderWindow m_mainWindow;
	sf::Color m_backgroundColor;
	sf::Clock m_deltaTimer;
	sf::Clock m_imguiClock;
	Interface m_interface;
	Camera m_camera;
	Background m_background;
	GUI m_gui;
};