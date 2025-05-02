#pragma once

#include <string>
#include <fstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "AssetManager.h"


class HealthManager
{
private:
	int& hp;

	sf::RectangleShape current_hp;
	sf::RectangleShape max_hp;
	sf::RectangleShape lost_hp;


	void Lerp(float dt);
public:
	HealthManager(AssetManager& assets, int& hp);


	void SetHp(int new_hp) { this->hp = new_hp; }
	void SetPosition(sf::Vector2f pos);

	int GetHp() const { return this->hp; }

	void Draw(sf::RenderWindow& window);
	void Update(float dt);
};

