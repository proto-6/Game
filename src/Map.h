#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "DEFINITIONS.h"


class Map : public sf::Drawable, public sf::Transformable
{
private:
	sf::VertexArray verticles;
	sf::Texture tileset;
	sf::RectangleShape map_body;
	int width; // In tiles, each one is 16x16
	int height; // In tiles, each one is 16x16
	

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	/// <summary>
	/// Adds tile with random texture to specified coords
	/// </summary>
	void AddTile(float x, float y);
public:
	Map(sf::Vector2u size);
	bool LoadTiles(sf::Vector2u window_size);
	
	// Getters
	
	/// <summary>
	/// In tiles (64px each)
	/// </summary>
	int GetWidth() const { return this->width; }
	/// <summary>
	/// In tiles (64px each)
	/// </summary>
	/// <returns></returns>
	int GetHeigth() const { return this->height; }
};

