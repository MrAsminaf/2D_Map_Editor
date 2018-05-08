#include "MainWindow.h"

MainWindow::MainWindow(int window_width, int window_height)
	:
	m_mainWindow(sf::VideoMode(window_width, window_height), "Map Editor"),
	m_backgroundColor( sf::Color(30, 30, 30, 55) ),
	m_interface(m_mainWindow),
	m_camera(m_mainWindow)
{
	m_mainWindow.resetGLStates();
}

void MainWindow::RunMainLoop()
{
	while (m_mainWindow.isOpen()) 
	{
		float temp = m_deltaTimer.restart().asSeconds();
		HandleWindowEvents();
		Input(temp);
		Update();
		Render();
	}
}

void MainWindow::Input(float delta_time)
{
	IfUserClickedTile();
	m_camera.Move(delta_time);
}

void MainWindow::Update()
{
	m_camera.Update(m_mainWindow);
	m_interface.Update();
}

void MainWindow::Render()
{
	m_mainWindow.clear(m_backgroundColor);
	m_interface.Draw();
	m_sfgui.Display(m_mainWindow);
	m_mainWindow.display();
}

void MainWindow::HandleWindowEvents()
{
	sf::Event sf_event;
		while (m_mainWindow.pollEvent(sf_event)) 
		{
			m_interface.HandleSFGUIEvents(sf_event);

			if (sf_event.type == sf::Event::Closed) 
				m_mainWindow.close();
			if (sf_event.type == sf::Event::MouseWheelMoved)
			{
				if (sf_event.mouseWheel.delta < 1)
					m_camera.ZoomOut();
				if (sf_event.mouseWheel.delta >= 1)
					m_camera.ZoomIn();
				if (sf_event.type == sf::Event::Resized)
				{
					// update the view to the new size of the window
					sf::FloatRect visibleArea(0.f, 0.f, float(sf_event.size.width), float(sf_event.size.height));
					m_mainWindow.setView(sf::View(visibleArea));
				}
			}
		}
}

void MainWindow::IfUserClickedTile()
{
	if (IfUserAddsTile())
		m_interface.AddTile();

	if (IfUserDeletsTile())
		m_interface.DeleteTile();
}

bool MainWindow::IfUserAddsTile()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_interface.GetCurrentChosenBlock() != TextureLoader::ENUM_NONE;
}

bool MainWindow::IfUserDeletsTile()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
}
 