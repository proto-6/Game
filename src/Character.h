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
	sf::Sprite _hero;
	Character::State _state;
	std::vector<std::shared_ptr<sf::Texture>> _animations;
	unsigned int _current_animation;
	float _animation_interval;
	float _elapsed_time;

public:
	// Constructors
	Character(AssetManager& manager);
	Character& operator=(const Character& other);


	// Setters
	void SetPosition(sf::Vector2f pos2);
	void SetPosition(float x, float y);
	void SetScale(sf::Vector2f scale);

	// Getters
	sf::Vector2f GetPosition() const { return _hero.getPosition(); };
	sf::Vector2f GetScale() const;

	// Core methods
	void Draw(sf::RenderWindow* window, float dt);
	void Update(float dt);

};

