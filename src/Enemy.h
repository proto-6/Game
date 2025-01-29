#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <random>
#include "GameData.h"



class Enemy
{
private:
	sf::Sprite enemy;
	std::vector<std::shared_ptr<sf::Texture>> run_animations;

	unsigned int current_animation;
	float animation_interval;
	float elapsed_time;
	float speed;

	// Methods 
	void RandomizePosition(std::mt19937& rng);
public:
	// Constructors
	Enemy(AssetManager& manager, std::mt19937& rng);
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


	// Getters
	sf::Vector2f GetPosition() const { return enemy.getPosition(); };
	sf::Vector2f GetScale() const { return this->enemy.getScale(); }
	float GetSpeed() const { return this->speed; }
	const sf::FloatRect& GetGlobalBounds();


	// Core methods
	void Draw(sf::RenderWindow* window, float dt);
	void UpdateAnimation(float dt);
	/// <summary>
	/// Makes enemies move towards hero and mirrors sprite so it seems like enemy is looking at hero
	/// </summary>
	void UpdateMovement(sf::Vector2f target_location, float dt);
};

