#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class TextureLoader
{
public:
	TextureLoader();
	enum ID
	{
		ENUM_NONE,
		ENUM_GRASS,
		ENUM_DIRT,
		ENUM_GRASS_ULDR,
		ENUM_GRASS_DLTR,
		ENUM_STONE,
		ENUM_DIRT_DLTR,
		ENUM_DIRT_TLDR
	};
	sf::Texture& GetTextureById(const ID texture_id);

private:
	void LoadAllTexturesFromFiles();
	void LoadOneTexture(const std::string filepath_to_texture);

private:
	std::vector<sf::Texture>m_textures;
};
