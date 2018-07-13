#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "BlockTypes.h"

struct TexturesInfo
{
	sf::Texture texture;
	std::string filepath;
};

class TextureManager
{
public:
	TextureManager();
	sf::Texture& GetTextureById(const int texture_id);

private:
	void LoadAllTexturesFromFiles();
	void LoadOneTexture(const std::string& filepath_to_texture);

private:
	std::vector<TexturesInfo>m_textures;
};