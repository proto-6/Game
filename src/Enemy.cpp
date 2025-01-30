#include "Enemy.h"
#include "DEFINITIONS.h"


void Enemy::RandomizePosition(std::mt19937& rng)
{
	std::uniform_real_distribution<float> dist_x(-2420.f, 2420.f);
	float expected_x = dist_x(rng);
	sf::Vector2f pos;
	if (expected_x >= 1920.f || expected_x <= -1920.f)
	{
		std::uniform_real_distribution<float> dist_y(-1580.f, 1580.f);
		pos = { expected_x, dist_y(rng) };
	}
	else
	{
		/*std::uniform_real_distribution<float> dist_y(-1580.f, 1580.f);*/
		std::uniform_real_distribution<float> dist_y(-500.f, 500.f);
		float expected_y = dist_y(rng);
		expected_y = expected_y > 0 ? expected_y + 1080.f : expected_y - 1080.f;
		pos = { expected_x, expected_y };
	}
	
	





	//// So enemies spawn outside of view
	//if (pos.x > 0) pos.x += 1920.f; 
	//else if (pos.x <= 0) pos.x -= 1920.f;
	//if (pos.y > 0) pos.y += 1080.f;
	//else if (pos.y <= 0) pos.y -= 1080.f;

	//if (std::abs(pos.x) > 3840.f) pos.x = -pos.x;
	//if (std::abs(pos.y) > 2240.f) pos.y = -pos.y;

	SetPosition(pos);
}

Enemy::Enemy(AssetManager& manager, std::mt19937& rng)
{
	
	LoadAnimations(manager);


	RandomizePosition(rng);
	animation_interval = 0.2f;
	elapsed_time = 0.f;
	enemy.setScale(4, 4);
	speed = 250.f;
}

Enemy& Enemy::operator=(const Enemy& other)
{
	if (this != &other)
	{
		this->run_animations = other.run_animations;
		this->current_animation = other.current_animation;
		this->enemy = other.enemy;
	}
	return *this;
}

void Enemy::LoadAnimations(AssetManager& manager)
{
	// Run animations
	manager.LoadTexture(Texture::EnemyRun0, "../resource/assets/enemy/lizard_m_run_anim_f0.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyRun0)));
	manager.LoadTexture(Texture::EnemyRun1, "../resource/assets/enemy/lizard_m_run_anim_f1.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyRun1)));
	manager.LoadTexture(Texture::EnemyRun2, "../resource/assets/enemy/lizard_m_run_anim_f2.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyRun2)));
	manager.LoadTexture(Texture::EnemyRun3, "../resource/assets/enemy/lizard_m_run_anim_f3.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::EnemyRun3)));

	// Setting initial texture to a Enemy
	current_animation = 0;
	enemy.setTexture(*run_animations[current_animation]);

}


const sf::FloatRect& Enemy::GetGlobalBounds()
{
	return this->enemy.getGlobalBounds();
}

void Enemy::Draw(sf::RenderWindow* window, float dt)
{
	
	window->draw(this->enemy);
}


void Enemy::UpdateAnimation(float dt)
{
	/*if (this->state == EnemyMovement::State::Running)
	{
		elapsed_time += dt * this->speed / 800.f;
	}*/
	elapsed_time += dt;
	if (elapsed_time >= animation_interval)
	{
		elapsed_time -= animation_interval;

		current_animation = (current_animation + 1) % run_animations.size(); // So vector doesn't overflow

		this->enemy.setTexture(*run_animations[current_animation]); // Set enemy texture to next one
		
	}
}

void Enemy::UpdateMovement(sf::Vector2f target, float dt)
{
	float offset_x_enemy = this->enemy.getGlobalBounds().width / 2.f;
	float offset_x_hero = this->enemy.getGlobalBounds().width / 2.f;
	if (this->enemy.getPosition().x + offset_x_enemy > target.x + offset_x_hero)
	{
		this->enemy.setTextureRect(
			sf::IntRect(16, 0,
				-16, 
				28
			));
	}
	
	sf::Vector2f move_val((target - this->GetPosition()));
	float vector_length = std::sqrt(std::pow(move_val.x, 2) + std::pow(move_val.y, 2));
	move_val /= vector_length;
	this->enemy.move(move_val * dt * speed);

	if (this->enemy.getPosition().x + offset_x_enemy < target.x + offset_x_hero)
	{
		this->enemy.setTextureRect(
			sf::IntRect(0, 0,
				16,
				28
			));
	}
}



