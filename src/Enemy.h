#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "GameData.h"

namespace EnemyMovement
{
	enum class State
	{
		Idle,
		Running
	};
}

class Enemy
{
private:
	sf::Sprite enemy;
	EnemyMovement::State state;
	std::vector<std::shared_ptr<sf::Texture>> idle_animations;
	std::vector<std::shared_ptr<sf::Texture>> run_animations;

	unsigned int current_animation;
	float animation_interval;
	float elapsed_time;
	sf::Vector2f direction; // Direction in x and y directions (positive directions are right and down, negative are opposite)
	float speed;

public:
	// Constructors
	Enemy(AssetManager& manager);
	Enemy& operator=(const Enemy& other);
	void LoadAnimations(AssetManager& manager);

	// Setters
	void SetPosition(sf::Vector2f pos2) { this->enemy.setPosition(pos2); }
	void SetPosition(float x, float y) { this->enemy.setPosition(x, y); }
	void Move(sf::Vector2f pos2) { this->enemy.move(pos2); }
	void Move(float x, float y) { this->enemy.move(x, y); }
	void SetScale(sf::Vector2f scale) { enemy.setScale(scale); }
	void SetScale(float x, float y) { enemy.setScale(x, y); }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetState(EnemyMovement::State state) { this->state = state; }


	// Getters
	sf::Vector2f GetPosition() const { return enemy.getPosition(); };
	sf::Vector2f GetScale() const { return this->enemy.getScale(); }
	EnemyMovement::State GetState() const { return this->state; }
	float GetSpeed() const { return this->speed; }
	const sf::FloatRect& GetGlobalBounds();


	// Core methods
	void Draw(sf::RenderWindow* window, float dt);
	void UpdateAnimation(float dt);
	void UpdateMovement(sf::Vector2f target);
};

