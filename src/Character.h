#pragma once
#include "Entity.h"

namespace CharacterMovement
{
	enum class State
	{
		Idle,
		Running
	};
}

class Character : public Entity
{
private:
	CharacterMovement::State state;
	std::vector<std::shared_ptr<sf::Texture>> idle_animations;
	std::vector<std::shared_ptr<sf::Texture>> run_animations;

	unsigned int current_animation;
	float animation_interval;
	float elapsed_time;
	sf::Vector2f velocity;
	float speed;

public:
	// Constructors
	Character(AssetManager& manager);
	Character& operator=(Character& other);
	virtual void LoadAnimations(AssetManager& manager) override;

	// Setters
	void SetDirection(float x, float y);
	void SetDirection(sf::Vector2f direction);
	void ClearDirection();
	void SetState(CharacterMovement::State state) { this->state = state; }
	

	// Getters
	sf::Vector2f GetDirection() const { return this->velocity; }
	sf::Vector2f GetVelocity() const { return this->velocity; }
	CharacterMovement::State GetState() const { return this->state; }

	// Core methods
	virtual void UpdateAnimation(float dt) override;
	void UpdateMovement(float dt);
};

