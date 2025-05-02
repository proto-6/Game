#pragma once

#include "SFML/Graphics.hpp"
#include "Timer.h"
#include "ScoreManager.h"
#include "AssetManager.h"
#include "HealthManager.h"

class HUD
{
private:
	Timer timer;
	HealthManager hp;
	ScoreManager score;

public:
	HUD(AssetManager& assets, HealthManager hp, Score::Type type);

	ScoreManager& GetScoreManager() { return score; }

	void Draw(sf::RenderWindow& target, sf::View& view);
	void Update(float dt);
	void AddToScore();


};

