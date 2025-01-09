#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "GameData.h"

namespace Movement
{
	enum class State
	{
		Idle,
		Running
	};
}

class Character
{
private:
	sf::Sprite _hero;
	Movement::State _state;
	std::vector<std::shared_ptr<sf::Texture>> _idle_animations;
	std::vector<std::shared_ptr<sf::Texture>> _run_animations;

	unsigned int _current_animation;
	float _animation_interval;
	float _elapsed_time;
	sf::Vector2f _direction; // Direction in x and y directions (positive directions are right and down, negative are opposite)
	float _speed;

public:
	// Constructors
	Character(AssetManager& manager);
	Character& operator=(const Character& other);
	void LoadAnimations(AssetManager& manager);

	// Setters
	void SetPosition(sf::Vector2f pos2);
	void SetPosition(float x, float y);
	void Move(sf::Vector2f pos2);
	void Move(float x, float y);
	void SetScale(sf::Vector2f scale);
	void SetScale(float x, float y);
	void SetSpeed(float speed);
	void SetDirection(float x, float y);
	void SetDirection(sf::Vector2f direction);
	void ClearDirection();
	void SetState(Movement::State state);

	// Getters
	sf::Vector2f GetPosition() const { return _hero.getPosition(); };
	sf::Vector2f GetScale() const;
	sf::Vector2f GetDirection();
	Movement::State GetState() const;
	float GetSpeed();

	// Core methods
	void Draw(sf::RenderWindow* window, float dt);
	void Update(float dt);
};

