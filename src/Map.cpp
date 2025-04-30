#include "Map.h"

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &tileset;

	// draw the vertex array
	target.draw(this->verticles, states);
    target.draw(this->map_body, states);
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

Map::Map(sf::Vector2u map_size)
    : width(0), height(0)
{
    LoadTiles(map_size);
    // Calculating size of a map using starting and ending cords 
    // (width * height * 4) - 1 - 2 means I'm using upper right cord of a tile
    map_body.setSize( 
        sf::Vector2f(verticles[(width * height * 4) - 1 - 2].position.x, verticles[(width * height * 4) - 1].position.y) -
        sf::Vector2f(verticles[0].position));
    map_body.setPosition(verticles[0].position);
    map_body.setOutlineColor(sf::Color(31, 25, 25));
    map_body.setOutlineThickness(12);
    map_body.setFillColor(sf::Color::Transparent);
    
}

bool Map::LoadTiles(sf::Vector2u map_size)
{
    map_size /= 4u;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 6);

    sf::Texture map;
    // Number TILE_SIZE is resolution of 1 tile, numbers 3 and 2 is amount of tiles I want to grab 
    if (!this->tileset.loadFromFile("../resource/assets/0x72_DungeonTilesetII_v1.7/atlas_floor-16x16.png", sf::IntRect({ 0, 0 }, { TILE_SIZE * 3, TILE_SIZE * 2 })))
    {
        return false;
    }
    this->width = map_size.x / TILE_SIZE;
    this->height = map_size.y / TILE_SIZE;
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


