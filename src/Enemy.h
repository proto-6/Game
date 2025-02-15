#pragma once
#include "Entity.h"
#include <random>



class Enemy : public Entity
{
private:
	std::vector<std::shared_ptr<sf::Texture>> run_animations;

	unsigned int current_animation;
	float animation_interval;
	float elapsed_time;

	// Methods 
	void RandomizePosition(std::mt19937& rng);
public:
	// Constructors
	Enemy(AssetManager& manager, std::mt19937& rng);//
	Enemy& operator=(const Enemy& other);//
	virtual void LoadAnimations(AssetManager& manager) override;//

	


	// Core methods
	virtual void UpdateAnimation(float dt) override;
	/// <summary>
	/// Makes enemies move towards hero and mirrors sprite so it seems like enemy is looking at hero
	/// </summary>
	void UpdateMovement(sf::Vector2f target, float dt);
};

