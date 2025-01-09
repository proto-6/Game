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
{
	
}

bool Map::LoadTiles(sf::Vector2u window_size)
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
	int width = window_size.x / TILE_SIZE + 1; 
	int height = window_size.y / TILE_SIZE + 1;

    // Calculate offsets for centering the map
    float offset_x = -(width * TILE_SIZE) / 2.0f;
    float offset_y = -(height * TILE_SIZE) / 2.0f;

    // Prepare vertex array
    this->_vertices.setPrimitiveType(sf::Quads);
    this->_vertices.resize(static_cast<size_t>(width * height * 4));

    // Generate tiles
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sf::Vertex* quad = &this->_vertices[(i + j * width) * 4];

            // Random tile index
            int tile_number = dist(rng) - 1;
            int tu = tile_number % 3;
            int tv = tile_number / 3;

            // Set positions
            quad[0].position = sf::Vector2f(offset_x + TILE_SIZE * i, offset_y + TILE_SIZE * j) * 4.f;
            quad[1].position = sf::Vector2f(offset_x + TILE_SIZE * (i + 1), offset_y + TILE_SIZE * j) * 4.f;
            quad[2].position = sf::Vector2f(offset_x + TILE_SIZE * (i + 1), offset_y + TILE_SIZE * (j + 1)) * 4.f;
            quad[3].position = sf::Vector2f(offset_x + TILE_SIZE * i, offset_y + TILE_SIZE * (j + 1)) * 4.f;

            // Set texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
        }
    }

	return true;
}
