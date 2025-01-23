#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "GameData.h"

namespace CharacterMovement
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
	sf::Sprite hero;
	CharacterMovement::State state;
	std::vector<std::shared_ptr<sf::Texture>> idle_animations;
	std::vector<std::shared_ptr<sf::Texture>> run_animations;

	unsigned int current_animation;
	float animation_interval;
	float elapsed_time;
	sf::Vector2f direction; // Direction in x and y directions (positive directions are right and down, negative are opposite)
	float speed;

public:
	// Constructors
	Character(AssetManager& manager);
	Character& operator=(const Character& other);
	void LoadAnimations(AssetManager& manager);

	// Setters
	void SetPosition(sf::Vector2f pos2) { this->hero.setPosition(pos2); }
	void SetPosition(float x, float y) { this->hero.setPosition(x, y); }
	void Move(sf::Vector2f pos2) { this->hero.move(pos2); }
	void Move(float x, float y) { this->hero.move(x, y); }
	void SetScale(sf::Vector2f scale) { hero.setScale(scale); }
	void SetScale(float x, float y) { hero.setScale(x, y); }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetDirection(float x, float y);
	void SetDirection(sf::Vector2f direction);
	void ClearDirection();
	void SetState(CharacterMovement::State state) { this->state = state; }
	

	// Getters
	sf::Vector2f GetPosition() const { return hero.getPosition(); };
	sf::Vector2f GetScale() const { return this->hero.getScale(); }
	sf::Vector2f GetDirection() const { return this->direction; }
	CharacterMovement::State GetState() const { return this->state; }
	float GetSpeed() const { return this->speed; }
	const sf::FloatRect& GetGlobalBounds();
	

	// Core methods
	void Draw(sf::RenderWindow* window, float dt);
	void UpdateAnimation(float dt);
};

