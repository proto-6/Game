#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "GameData.h"
#include "DEFINITIONS.h"


class Entity
{
protected:
	sf::Sprite entity;
	float speed;
public:
	// Constructors
	Entity();
	virtual void LoadAnimations(AssetManager& manager) = 0;

	// Setters
	void SetPosition(sf::Vector2f pos2) { this->entity.setPosition(pos2); }
	void SetPosition(float x, float y) { this->entity.setPosition(x, y); }
	void Move(sf::Vector2f pos2) { this->entity.move(pos2); }
	void Move(float x, float y) { this->entity.move(x, y); }
	void SetScale(sf::Vector2f scale) { entity.setScale(scale); }
	void SetScale(float x, float y) { entity.setScale(x, y); }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetOrigin(float x, float y) { this->entity.setOrigin(x, y); }
	void SetOrigin(sf::Vector2f origin) { this->entity.setOrigin(origin); }


	// Getters
	sf::Vector2f GetPosition() const { return entity.getPosition(); }
	sf::Vector2f GetScale() const { return this->entity.getScale(); }
	float GetSpeed() const { return this->speed; }
	const sf::FloatRect& GetGlobalBounds() { return this->entity.getGlobalBounds(); }
	const sf::FloatRect& GetLocalBounds() { return this->entity.getLocalBounds(); }


	// Core methods
	void Draw(sf::RenderWindow* window, float dt) { window->draw(this->entity); }
	virtual void UpdateAnimation(float dt) = 0;
};

