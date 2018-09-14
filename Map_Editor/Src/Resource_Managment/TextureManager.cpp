#include "TextureManager.h"

std::vector<TexturesInfo> TextureManager::m_textures;

TextureManager::TextureManager()
{
	LoadAllTexturesFromFiles();
}

sf::Texture& TextureManager::GetTextureById(const int texture_id)
{
	return m_textures.at(texture_id - 'a').texture;
}

void TextureManager::LoadAllTexturesFromFiles()
{
	LoadOneTexture("Res/terrain_platform_left.png"		, BlockTypes::ENUM_TERRAIN_PLATFORM_LEFT);
	LoadOneTexture("Res/terrain_platform_center.png"	, BlockTypes::ENUM_TERRAIN_PLATFORM_CENTER);
	LoadOneTexture("Res/terrain_platform_right.png"		, BlockTypes::ENUM_TERRAIN_PLATFROM_RIGHT);

	LoadOneTexture("Res/terrain_top_left.png"			, BlockTypes::ENUM_TERRAIN_TOP_LEFT);
	LoadOneTexture("Res/terrain_top_center.png"			, BlockTypes::ENUM_TERRAIN_TOP_CENTER);
	LoadOneTexture("Res/terrain_top_right.png"			, BlockTypes::ENUM_TERRAIN_TOP_RIGHT);

	LoadOneTexture("Res/terrain_bottom_left.png"		, BlockTypes::ENUM_TERRAIN_BOTTOM_LEFT);
	LoadOneTexture("Res/terrain_bottom_center.png"		, BlockTypes::ENUM_TERRAIN_BOTTOM_CENTER);
	LoadOneTexture("Res/terrain_bottom_right.png"		, BlockTypes::ENUM_TERRAIN_BOTTOM_RIGHT);

	LoadOneTexture("Res/terrain_center_left.png"		, BlockTypes::ENUM_TERRAIN_CENTER_LEFT);
	LoadOneTexture("Res/terrain_center.png"				, BlockTypes::ENUM_TERRAIN_CENTER);
	LoadOneTexture("Res/terrain_center_right.png"		, BlockTypes::ENUM_TERRAIN_CENTER_RIGHT);
}

void TextureManager::LoadOneTexture(const std::string& filepath_to_texture, const BlockTypes& block_type)
{
	sf::Texture tempTexture;
	tempTexture.loadFromFile(filepath_to_texture);
	
	TexturesInfo t{ tempTexture, filepath_to_texture, block_type };
	m_textures.push_back(t);
}
