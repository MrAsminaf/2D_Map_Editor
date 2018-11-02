#pragma once

#include "imgui.h"
#include "imgui-sfml-master/imgui-SFML.h"
#include <SFML/Graphics.hpp>

#include "Interface/Camera.h"
#include "Interface/Layout.h"
#include "Interface/GUI.h"
#include "Interface/Foreground.h"
#include "Resource_Managment/BlockTypes.h"

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
	Foreground m_foreground;
	Camera m_camera;
	Layout m_layout;
	GUI m_gui;
};