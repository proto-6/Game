#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "MagicAttack.h"
#include <memory>

namespace CharacterMovement
{
	enum class State
	{
		Idle,
		Running,
		Pose
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

	// Attack-related
	// bool represents if attack is on the field
	std::pair<std::shared_ptr<MagicAttack>, bool> attack;
	float attack_cooldown;

	const float default_attack_cooldown = 3.f;

public:
	// Constructors
	Character(AssetManager& manager);
	Character& operator=(Character& other);
	virtual void LoadAnimations(AssetManager& manager) override;

	// Attack-related
	void UpdateAttack(float dt, sf::RenderWindow& window, const sf::FloatRect& map_box);

	// Setters
	void SetDirection(float x, float y);
	void SetDirection(sf::Vector2f direction);
	void ClearDirection();
	void SetState(CharacterMovement::State state) { this->state = state; }
	void ReceiveDamage(Enemy& enemy);
	

	// Getters
	sf::Vector2f GetDirection() const { return this->velocity; }
	sf::Vector2f GetVelocity() const { return this->velocity; }
	CharacterMovement::State GetState() const { return this->state; }
	bool IsAttackUsed() { return this->attack.second; }
	sf::FloatRect GetAttackCollisionBox() { return this->attack.first->GetGlobalBounds(); }
	float GetAttackDamage() { return this->attack.first->GetDamage(); }

	// Core methods
	virtual void UpdateAnimation(float dt) override;
	void UpdateMovement(float dt);
	void DrawAttack(sf::RenderWindow* window);
};

