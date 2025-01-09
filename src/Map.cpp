#include "Map.h"

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &_tileset;

	// draw the vertex array
	target.draw(this->_vertices, states);
}

Map::Map()
	: _tile_size(16)
{
	
}

bool Map::LoadTiles()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 6);

	sf::Texture map;
	// Number 16 is resolution of 1 tile, numbers 3 and 2 is amount of tiles I want to grab 
	if (!this->_tileset.loadFromFile("../resource/assets/0x72_DungeonTilesetII_v1.7/atlas_floor-16x16.png", sf::IntRect({ 0, 0 }, {16*3, 16*2}))) 
	{
		return false;
	}
	int width = 30;
	int height = 17;
	this->_vertices.setPrimitiveType(sf::Quads);
	this->_vertices.resize(width * height * 4);
	
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			sf::Vertex* quad = &this->_vertices[(i + j * width) * 4];

			int tile_number = dist(rng) - 1;
			int tu = tile_number % 3; // Горизонтальне положення в тайлсеті
			int tv = tile_number / 3; // Вертикальне положення в тайлсеті

			quad[0].position = sf::Vector2f(this->_tile_size * i, this->_tile_size * j) * 4.f;
			quad[1].position = sf::Vector2f(this->_tile_size * (i + 1) , this->_tile_size * j) * 4.f;
			quad[2].position = sf::Vector2f(this->_tile_size * (i + 1), this->_tile_size * (j + 1)) * 4.f;
			quad[3].position = sf::Vector2f(this->_tile_size * i, this->_tile_size * (j + 1)) * 4.f;
			
			quad[0].texCoords = sf::Vector2f(tu * _tile_size, tv * _tile_size);
			quad[1].texCoords = sf::Vector2f((tu + 1) * _tile_size, tv * _tile_size);
			quad[2].texCoords = sf::Vector2f((tu + 1) * _tile_size, (tv + 1) * _tile_size);
			quad[3].texCoords = sf::Vector2f(tu * _tile_size, (tv + 1) * _tile_size);
		}
	}

	return true;
}
