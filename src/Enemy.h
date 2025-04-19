#pragma once
#include "Entity.h"
#include <random>



class Enemy : public Entity
{
public:
	enum Facing {
		Left,
		Right
	};
	enum State
	{
		Move,
		Stun,
		Pre_Attack,
		Attack
	};
private:
	std::vector<std::shared_ptr<sf::Texture>> run_animations;

	unsigned int current_animation;
	float animation_interval;
	float elapsed_time;
	Facing facing;
	State state;

	// Attack-Related
	int current_dash_stage;
	float stun;
	float dash_attack_time;
	float attack_range;
	float attack_cooldown;
	float time_until_attack;
	sf::Vector2f attack_target;
	sf::Vector2f dash_move_amount;
	sf::RectangleShape attack_box;
	const int default_amount_dash_stages = 4;
	const float default_dash_attack_time = 0.12f;
	const float after_attack_stun = 0.8f;
	const float attack_time_delay = 1.6f;
	const float default_collision_damage = 10.f;
	const float dash_attack_damage = 15.f;
	const float default_attack_cooldown = 3.f;
	const sf::Color attack_color = sf::Color(255, 0, 0, 120);



	// Inner methods 
	void UpdateEffects(float dt);
	void RandomizePosition(std::mt19937& rng);
	void UpdateFacingSide(sf::Vector2f target);
public:
	// Constructors
	Enemy(AssetManager& manager, std::mt19937& rng);//
	Enemy& operator=(const Enemy& other);//
	virtual void LoadAnimations(AssetManager& manager) override;//

	// Getters
	State GetState() const { return this->state; }
	float GetDamage();

	// Core methods
	virtual void UpdateAnimation(float dt) override;
	/// <summary>
	/// Makes enemies move towards hero and mirrors sprite so it seems like enemy is looking at hero
	/// </summary>
	void UpdateMovement(sf::Vector2f target, float dt);
	void UpdateAttack(sf::Vector2f target, float dt, sf::RenderWindow& window);
	

	void Draw(sf::RenderWindow* window, float dt) override { 
		window->draw(this->entity); 
		window->draw(this->attack_box);
	}
	void Draw(sf::RenderWindow* window, sf::Shader& shader, float dt) override { window->draw(this->entity, &shader); }
};

