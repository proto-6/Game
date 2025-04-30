#pragma once
#include <sstream>
#include <iomanip>
#include "SFML/Graphics.hpp"
#include "Timer.h"
#include "ScoreManager.h"
#include "AssetManager.h"

class HUD
{
private:
	Timer timer;
	int& hp;
	ScoreManager score;
	sf::Text hp_text;

public:
	HUD(AssetManager& assets, int& hp);

	void Draw(sf::RenderWindow& target, sf::View& view);
	void Update();
	void AddToScore();


};

