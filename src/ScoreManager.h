#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "AssetManager.h"

class ScoreManager
{
private:
	int score;
	sf::Text text;


	std::string GetString();
public:
	ScoreManager(AssetManager& assets);

	void SetScore(int new_score);
	int GetScore() const { return this->score; }
	void AddToScore(int add_val);

	void Draw(sf::RenderWindow& window);
};

