#include "AssetManager.h"

#include <assert.h>

void AssetManager::LoadTexture(Texture::Type name, std::string filepath)
{
	sf::Texture tex;
	
	tex.loadFromFile(filepath);
	this->textures[name] = tex;
}

void AssetManager::LoadFont(Font::Type name, std::string filepath)
{
	sf::Font font;

	font.loadFromFile(filepath);
	this->fonts[name] = font;
}

sf::Texture& AssetManager::GetTexture(Texture::Type name)
{
	return this->textures.at(name);
}

sf::Font& AssetManager::GetFont(Font::Type name)
{
	return this->fonts.at(name);
}
