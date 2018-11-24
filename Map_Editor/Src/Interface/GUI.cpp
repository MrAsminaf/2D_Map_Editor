#include "GUI.h"


void GUI::Update(sf::Color& bg_color)
{
	ImGui::Begin("Colors"); // begin window
	if (ImGui::ColorEdit3("Background color", m_backgroundColorBuffer)) 
	{
		Layout::m_gradientColor.r = static_cast<sf::Uint8>(m_backgroundColorBuffer[0] * 255.f);
		Layout::m_gradientColor.g = static_cast<sf::Uint8>(m_backgroundColorBuffer[1] * 255.f);
		Layout::m_gradientColor.b = static_cast<sf::Uint8>(m_backgroundColorBuffer[2] * 255.f);
		
		bg_color.r = static_cast<sf::Uint8>(m_backgroundColorBuffer[0] * 255.f);
		bg_color.g = static_cast<sf::Uint8>(m_backgroundColorBuffer[1] * 255.f);
		bg_color.b = static_cast<sf::Uint8>(m_backgroundColorBuffer[2] * 255.f);
	}

	if (ImGui::ColorEdit3("Net color", m_netColorBuffer))
	{
		Layout::m_netColor.r = static_cast<sf::Uint8>(m_netColorBuffer[0] * 255.f);
		Layout::m_netColor.g = static_cast<sf::Uint8>(m_netColorBuffer[1] * 255.f);
		Layout::m_netColor.b = static_cast<sf::Uint8>(m_netColorBuffer[2] * 255.f);
	}

	ImGui::End(); // end window

	ImGui::Begin("Blocks");
	if (ImGui::Button("Generate"))
	{
		m_generator.Generate();
	}

	ImGui::Begin("Mode");
	if (ImGui::Button("Foreground"))
	{
		Layout::SetMode(Mode::FOREGROUND);
	}
	ImGui::SameLine(100.f);
	if (ImGui::Button("Background"))
	{
		Layout::SetMode(Mode::BACKGROUND);
	}
	ImGui::End();

	for (const auto& texture : TextureManager::m_textures)
	{
		ImGui::Spacing();
		ImGui::Spacing();

		if (texture.blockType == BlockTypes::ENUM_MIDGROUND_LEFT_A || texture.blockType == BlockTypes::ENUM_MIDGROUND_LEFT_A_SHADOWED
			|| texture.blockType == BlockTypes::ENUM_MIDGROUND_RIGHT_A || texture.blockType == BlockTypes::ENUM_MIDGROUND_RIGHT_A_SHADOWED)
		{
			if (ImGui::ImageButton(texture.texture, sf::Vector2f(50, 25)))
			{
				Foreground::GetMouseHighlight().setTexture(&texture.texture, true);
				Foreground::GetMouseHighlight().setSize(sf::Vector2f(32, 16));
				Foreground::GetMouseHighlight().setFillColor(sf::Color(255, 255, 255, 100));
				Foreground::GetCurrentBlock() = texture.blockType;
			}
			continue;
		}

		if (ImGui::ImageButton(texture.texture, sf::Vector2f(50, 50)))
		{
			Foreground::GetMouseHighlight().setTexture(&texture.texture, true);
			Foreground::GetMouseHighlight().setSize(sf::Vector2f(16, 16));
			Foreground::GetMouseHighlight().setFillColor(sf::Color(255, 255, 255, 100));
			Foreground::GetCurrentBlock() = texture.blockType;
		}
	}
	ImGui::End();

	ImGui::Begin("Load files");
	char buf1[256] = "";
	char buf2[256] = "";
	ImGui::Text("Write name of the file and click 'Enter'");
	if (ImGui::InputText("Foreground", buf1, 256, 32))
	{
		m_mapFromFileLoader.LoadFile(buf1, Foreground::GetTilesContainer(Mode::FOREGROUND));
	}
	if(ImGui::InputText("Background", buf2, 256, 32))
	{
		m_mapFromFileLoader.LoadFile(buf2, Foreground::GetTilesContainer(Mode::BACKGROUND));
	}
	ImGui::End();
}
