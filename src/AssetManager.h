#pragma once

#include "DEFINITIONS.h"

#include <map>

#include <SFML/Graphics.hpp>

class AssetManager
{
public:
	AssetManager() {}
	~AssetManager() {}

	void LoadTexture(Texture::Type name, std::string filepath);
	void LoadFont(Font::Type name, std::string filepath);
	
	sf::Texture& GetTexture(Texture::Type name);
	sf::Font& GetFont(Font::Type name);

private:
	std::map<Texture::Type, sf::Texture> _textures;
	std::map<Font::Type, sf::Font> _fonts;

};

