#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "DEFINITIONS.h"


class Map : public sf::Drawable, public sf::Transformable
{
private:
	sf::VertexArray _vertices;
	sf::Texture _tileset;


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Map();
	bool LoadTiles(sf::Vector2u window_size);
};

