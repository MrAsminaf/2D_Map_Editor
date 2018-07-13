#include "TextureManager.h"

TextureManager::TextureManager()
{
	LoadAllTexturesFromFiles();
}

sf::Texture& TextureManager::GetTextureById(const int texture_id)
{
	return m_textures.at(texture_id - 1).texture;
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
	sf::Texture tempTexture;
	tempTexture.loadFromFile(filepath_to_texture);
	
	TexturesInfo t{ tempTexture, filepath_to_texture };
	m_textures.push_back(t);

	//GUI::AddButtonForChosingBlock(filepath_to_texture, )
}
