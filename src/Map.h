#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>


class Map : public sf::Drawable, public sf::Transformable
{
private:
	sf::VertexArray _vertices;
	sf::Texture _tileset;
	int _tile_size;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Map();
	bool LoadTiles();
};

