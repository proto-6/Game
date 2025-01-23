#include "Map.h"

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &tileset;

	// draw the vertex array
	target.draw(this->verticles, states);
}


void Map::AddTile(float x, float y)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 6);

    int tile_number = dist(rng) - 1;
    int tu = tile_number % 3;
    int tv = tile_number / 3;

    sf::Vertex quad[4];

    // Set positions
    quad[0].position = sf::Vector2f(x, y) * 4.f;
    quad[1].position = sf::Vector2f(TILE_SIZE + x, y) * 4.f;
    quad[2].position = sf::Vector2f(TILE_SIZE + x, TILE_SIZE + y) * 4.f;
    quad[3].position = sf::Vector2f(x, TILE_SIZE + y) * 4.f;

    // Set texture coordinates
    quad[0].texCoords = sf::Vector2f(static_cast<float>(tu) * TILE_SIZE, static_cast<float>(tv) * TILE_SIZE);
    quad[1].texCoords = sf::Vector2f(static_cast<float>(tu + 1) * TILE_SIZE, static_cast<float>(tv) * TILE_SIZE);
    quad[2].texCoords = sf::Vector2f(static_cast<float>(tu + 1) * TILE_SIZE, static_cast<float>(tv + 1) * TILE_SIZE);
    quad[3].texCoords = sf::Vector2f(static_cast<float>(tu) * TILE_SIZE, static_cast<float>(tv + 1) * TILE_SIZE);

    for (size_t i = 0; i < 4; i++)
    {
        this->verticles.append(quad[i]);
    }
}

Map::Map()
    : hi_cords_down(0.f), hi_cords_up(0.f), hi_cords_left(0.f), hi_cords_right(0.f),
    width(0), height(0)
{
	
}

bool Map::LoadTiles(sf::Vector2u window_size)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 6);

    sf::Texture map;
    // Number TILE_SIZE is resolution of 1 tile, numbers 3 and 2 is amount of tiles I want to grab 
    if (!this->tileset.loadFromFile("../resource/assets/0x72_DungeonTilesetII_v1.7/atlas_floor-16x16.png", sf::IntRect({ 0, 0 }, { TILE_SIZE * 3, TILE_SIZE * 2 })))
    {
        return false;
    }
    this->width = window_size.x / TILE_SIZE;
    this->height = window_size.y / TILE_SIZE * 1.05;
    this->verticles.setPrimitiveType(sf::Quads);
    

    for (int i = -this->width / 2; i < this->width / 2; i++)
    {
        for (int j = -this->height / 2; j < this->height / 2; j++)
        {
            AddTile(i * TILE_SIZE, j * TILE_SIZE);
        }
    }

    return true;
}


