#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "BlockTypes.h"

class TextureManager
{
public:
	TextureManager();
	sf::Texture& GetTextureById(const int texture_id);

private:
	void LoadAllTexturesFromFiles();
	void LoadOneTexture(const std::string& filepath_to_texture);

private:
	std::vector<sf::Texture>m_textures;
};
