#pragma once

#include "imgui.h"
#include "imgui-sfml-master/imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream> // debug
#include "BlockTypes.h"

struct TexturesInfo
{
	sf::Texture texture;
	std::string filepath;
	BlockTypes blockType;
};

class TextureManager
{
public:
	TextureManager();
	sf::Texture& GetTextureById(const int texture_id);

private:
	void LoadAllTexturesFromFiles();
	void LoadOneTexture(const std::string& filepath_to_texture, const BlockTypes& block_type);

public:
	static std::vector<TexturesInfo>m_textures;
};