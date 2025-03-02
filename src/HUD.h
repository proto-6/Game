#pragma once
#include <sstream>
#include <iomanip>
#include "SFML/Graphics.hpp"
#include "Timer.h"
#include "AssetManager.h"

class HUD
{
private:
	Timer& timer;
	float& hp;
	sf::Text hp_text;

public:
	HUD(AssetManager& assets, Timer& timer, float& hp);

	void Draw(sf::RenderWindow& target, sf::View& view);


};

