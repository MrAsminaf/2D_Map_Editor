#include "TextureManager.h"

TextureManager::TextureManager()
{
	LoadAllTexturesFromFiles();
}

sf::Texture& TextureManager::GetTextureById(const int texture_id)
{
	return m_textures.at(texture_id-1);
}

void TextureManager::LoadAllTexturesFromFiles()
{
	LoadOneTexture("grass.png");
	LoadOneTexture("dirt.png");
	LoadOneTexture("grass_uldr.png");
	LoadOneTexture("grass_dltr.png");
	LoadOneTexture("stone.png");
	LoadOneTexture("dirt_dltr.png");
	LoadOneTexture("dirt_tldr.png");
	LoadOneTexture("terrain_platform_left.png");
}

void TextureManager::LoadOneTexture(const std::string& filepath_to_texture)
{
	m_textures.resize(m_textures.size() + 1);
	m_textures.at(m_textures.size() - 1).loadFromFile(filepath_to_texture);
}
