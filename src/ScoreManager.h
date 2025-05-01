#pragma once

#include <string>
#include <fstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "AssetManager.h"

namespace Score {
	enum Type
	{
		In_Game,
		Hi_Score
	};
}

class ScoreManager
{
private:
	int score;
	sf::Text text;

	Score::Type type;


	std::string GetString();
public:
	ScoreManager(AssetManager& assets, Score::Type type);
	ScoreManager(AssetManager& assets, Score::Type type, int score);

	void LoadScoreFromFile();
	/// <summary>
	/// Saves score if only current one is higher than the one that is saved in file
	/// </summary>
	void SaveScoreInFile() const;

	void SetScore(int new_score);
	void SetPosition(sf::Vector2f pos);

	int GetScore() const { return this->score; }
	void AddToScore(int add_val);

	void Draw(sf::RenderWindow& window);
};

