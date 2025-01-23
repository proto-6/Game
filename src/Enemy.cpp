#include "Enemy.h"
#include "DEFINITIONS.h"


Enemy::Enemy(AssetManager& manager)
{
	LoadAnimations(manager);


	enemy.setPosition(sf::Vector2f(0, 0));
	animation_interval = 0.2f;
	elapsed_time = 0.f;
	enemy.setScale(4, 4);
	direction.x = 0.f;
	direction.y = 0.f;
	speed = 500.f;
}

Enemy& Enemy::operator=(const Enemy& other)
{
	if (this != &other)
	{
		this->idle_animations = other.idle_animations;
		this->run_animations = other.run_animations;
		this->current_animation = other.current_animation;
		this->enemy = other.enemy;
		this->state = other.state;
	}
	return *this;
}

void Enemy::LoadAnimations(AssetManager& manager)
{
	// Loading Enemy idle animations into asset manager and adding it into an array so we can switch textures as we go
	// Idle animations
	manager.LoadTexture(Texture::EnemyIdle0, "../resource/assets/enemy/lizard_m_idle_anim_f0.png");
	idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyIdle0)));
	manager.LoadTexture(Texture::EnemyIdle1, "../resource/assets/enemy/lizard_m_idle_anim_f1.png");
	idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyIdle1)));
	manager.LoadTexture(Texture::EnemyIdle2, "../resource/assets/enemy/lizard_m_idle_anim_f2.png");
	idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyIdle2)));
	manager.LoadTexture(Texture::EnemyIdle3, "../resource/assets/enemy/lizard_m_idle_anim_f3.png");
	idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyIdle3)));

	// Run animations
	manager.LoadTexture(Texture::EnemyRun0, "../resource/assets/enemy/lizard_m_run_anim_f0.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyRun0)));
	manager.LoadTexture(Texture::EnemyRun1, "../resource/assets/enemy/lizard_m_run_anim_f0.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyRun1)));
	manager.LoadTexture(Texture::EnemyRun2, "../resource/assets/enemy/lizard_m_run_anim_f0.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyRun2)));
	manager.LoadTexture(Texture::EnemyRun3, "../resource/assets/enemy/lizard_m_run_anim_f0.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyRun3)));

	// Setting initial texture to a Enemy
	current_animation = 0;
	enemy.setTexture(*idle_animations[current_animation]);
	state = EnemyMovement::State::Idle;
}


const sf::FloatRect& Enemy::GetGlobalBounds()
{
	return this->enemy.getGlobalBounds();
}

void Enemy::Draw(sf::RenderWindow* window, float dt)
{
	window->draw(this->enemy);
}

#include <iostream>

void Enemy::UpdateAnimation(float dt)
{
	if (this->state == EnemyMovement::State::Running)
	{
		elapsed_time += dt * this->speed / 800.f;
	}
	elapsed_time += dt / 1.5f;
	if (elapsed_time >= animation_interval)
	{
		elapsed_time -= animation_interval;

		switch (state)
		{
		case EnemyMovement::State::Idle:
			std::cout << "Idle" << std::endl;
			current_animation = (current_animation + 1) % idle_animations.size(); // So vector doesn't overflow

			this->enemy.setTexture(*idle_animations[current_animation]); // Set enemy texture to next one
			break;
		case EnemyMovement::State::Running:
			std::cout << "Running" << std::endl;
			current_animation = (current_animation + 1) % run_animations.size(); // So vector doesn't overflow

			this->enemy.setTexture(*run_animations[current_animation]); // Set enemy texture to next one
			break;

		default:
			break;
		}
	}
}

void Enemy::UpdateMovement(sf::Vector2f target)
{

}



