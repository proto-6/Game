#include "AssetManager.h"

#include <assert.h>

void AssetManager::LoadTexture(Texture::Type name, std::string filepath)
{
	sf::Texture tex;
	
	tex.loadFromFile(filepath);
	this->_textures[name] = tex;
}

void AssetManager::LoadFont(Font::Type name, std::string filepath)
{
	sf::Font font;

	font.loadFromFile(filepath);
	this->_fonts[name] = font;
}

sf::Texture& AssetManager::GetTexture(Texture::Type name)
{
	return this->_textures.at(name);
}

sf::Font& AssetManager::GetFont(Font::Type name)
{
	return this->_fonts.at(name);
}
