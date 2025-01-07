#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "GameData.h"


class Character
{
	enum class State
	{
		Idle
	};

private:
	sf::Sprite hero;
	Character::State state;
	std::vector<std::shared_ptr<sf::Texture>> animations;
	unsigned int current_animation;
	float animation_interval;
	float elapsed_time;

public:
	Character(AssetManager& manager);
	Character& operator=(const Character& other);

	void Draw(sf::RenderWindow* window, float dt);
	void Update(float dt);
	void SetPosition(sf::Vector2f& pos2);
	sf::Vector2f GetPosition() const { return hero.getPosition(); };


};

