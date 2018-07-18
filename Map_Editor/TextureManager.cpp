#include "TextureManager.h"

std::vector<TexturesInfo> TextureManager::m_textures;

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
	/*LoadOneTexture("grass.png");
	LoadOneTexture("dirt.png");
	LoadOneTexture("grass_uldr.png");
	LoadOneTexture("grass_dltr.png");
	LoadOneTexture("stone.png");
	LoadOneTexture("dirt_dltr.png");
	LoadOneTexture("dirt_tldr.png");*/

	LoadOneTexture("terrain_platform_left.png"		, BlockTypes::ENUM_TERRAIN_PLATFORM_LEFT);
	LoadOneTexture("terrain_platform_center.png"	, BlockTypes::ENUM_TERRAIN_PLATFORM_CENTER);
	LoadOneTexture("terrain_platform_right.png"		, BlockTypes::ENUM_TERRAIN_PLATFROM_RIGHT);
	LoadOneTexture("terrain_top_left.png"			, BlockTypes::ENUM_TERRAIN_TOP_LEFT);
	LoadOneTexture("terrain_top_center.png"			, BlockTypes::ENUM_TERRAIN_TOP_CENTER);
	LoadOneTexture("terrain_top_right.png"			, BlockTypes::ENUM_TERRAIN_TOP_RIGHT);
}

void TextureManager::LoadOneTexture(const std::string& filepath_to_texture, const BlockTypes& block_type)
{
	sf::Texture tempTexture;
	tempTexture.loadFromFile(filepath_to_texture);
	
	TexturesInfo t{ tempTexture, filepath_to_texture, block_type };
	m_textures.push_back(t);
}
