#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
	LoadAllTexturesFromFiles();
}

sf::Texture& TextureLoader::GetTextureById(const ID texture_id)
{
	return m_textures.at(texture_id-1);
}

void TextureLoader::LoadAllTexturesFromFiles()
{
	LoadOneTexture("grass.png");
	LoadOneTexture("dirt.png");
	LoadOneTexture("grass_uldr.png");
	LoadOneTexture("grass_dltr.png");
	LoadOneTexture("stone.png");
	LoadOneTexture("dirt_dltr.png");
	LoadOneTexture("dirt_tldr.png");
}

void TextureLoader::LoadOneTexture(const std::string filepath_to_texture)
{
	m_textures.resize(m_textures.size() + 1);
	m_textures.at(m_textures.size() - 1).loadFromFile(filepath_to_texture);
}
