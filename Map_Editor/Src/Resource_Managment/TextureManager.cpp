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

	LoadOneTexture("Res/midground_left_B_shadowed.png"	, BlockTypes::ENUM_MIDGROUND_LEFT_B_SHADOWED);
	LoadOneTexture("Res/midground_left_B.png"			, BlockTypes::ENUM_MIDGROUND_LEFT_B);

	LoadOneTexture("Res/midground_right_B_shadowed.png"	, BlockTypes::ENUM_MIDGROUND_RIGHT_B_SHADOWED);
	LoadOneTexture("Res/midground_right_B.png"			, BlockTypes::ENUM_MIDGROUND_RIGHT_B);

	LoadOneTexture("Res/midground_center.png"			, BlockTypes::ENUM_MIDGROUND_CENTER);

	LoadOneTexture("Res/midground_left_A.png"			, BlockTypes::ENUM_MIDGROUND_LEFT_A);
	LoadOneTexture("Res/midground_left_A_shadowed.png"	, BlockTypes::ENUM_MIDGROUND_LEFT_A_SHADOWED);

	LoadOneTexture("Res/midground_right_A.png"			, BlockTypes::ENUM_MIDGROUND_RIGHT_A);
	LoadOneTexture("Res/midground_right_A_shadowed.png"	, BlockTypes::ENUM_MIDGROUND_RIGHT_A_SHADOWED);
}

void TextureManager::LoadOneTexture(const std::string& filepath_to_texture, const BlockTypes& block_type)
{
	sf::Texture tempTexture;
	tempTexture.loadFromFile(filepath_to_texture);
	
	TexturesInfo t{ tempTexture, filepath_to_texture, block_type };
	m_textures.push_back(t);
}
