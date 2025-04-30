#include "Enemy.h"
#include "DEFINITIONS.h"


void Enemy::UpdateEffects(float dt)
{
	this->stun -= dt;

	if (this->stun <= 0 && this->state == State::Stun)
	{
		this->state = State::Move;
	}
	else if (this->stun > 0) {
		this->state = State::Stun;
	}
}

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
		std::uniform_real_distribution<float> dist_y(-500.f, 500.f);
		float expected_y = dist_y(rng);
		expected_y = expected_y > 0 ? expected_y + 1080.f : expected_y - 1080.f;
		pos = { expected_x, expected_y };
	}
	
	






	SetPosition(pos);
}

Enemy::Enemy(AssetManager& manager, std::mt19937& rng)
{
	
	LoadAnimations(manager);


	RandomizePosition(rng);
	animation_interval = 0.2f;
	elapsed_time = 0.f;
	entity.setScale(4, 4);
	speed = 250.f;
	state = State::Move;
	attack_range = 220.f;
	stun = 0;
	time_until_attack = Enemy_Consts::attack_time_delay;
	attack_cooldown = Enemy_Consts::default_attack_cooldown;
	current_dash_stage = 0;
	dash_attack_time = 0;
	dash_move_amount = sf::Vector2f{ 0,0 };
}

Enemy& Enemy::operator=(const Enemy& other)
{
	if (this != &other)
	{
		this->run_animations = other.run_animations;
		this->current_animation = other.current_animation;
		this->entity = other.entity;
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
	entity.setTexture(*run_animations[current_animation]);

}


float Enemy::GetDamage()
{
	if (this->state == State::Attack)
	{
		return Enemy_Consts::dash_attack_damage;
	}
	else
	{
		return Enemy_Consts::default_collision_damage;
	}
}


void Enemy::UpdateAnimation(float dt)
{
	elapsed_time += dt;
	if (elapsed_time >= animation_interval)
	{
		if (this->state == State::Move)
		{
			elapsed_time -= animation_interval;

			current_animation = (current_animation + 1) % run_animations.size(); // So vector doesn't overflow

			this->entity.setTexture(*run_animations[current_animation]); // Set entity texture to next one
		}
		else {
			current_animation = 0;
			this->entity.setTexture(*run_animations[current_animation]);
		}
		
		
	}
}

void Enemy::UpdateMovement(sf::Vector2f target, float dt)
{
	sf::Vector2f half_entity = this->GetGlobalBounds().getSize() / 2.f;
	
	
	sf::Vector2f move_val((target - this->GetPosition() - this->GetGlobalBounds().getSize() / 2.f));
	float vector_length = static_cast<float>(std::sqrt(std::pow(move_val.x, 2) + std::pow(move_val.y, 2)));
	move_val /= vector_length;
	
	if (std::sqrt(std::pow(target.x - this->GetPosition().x - half_entity.x, 2) + std::pow(target.y - this->GetPosition().y - half_entity.y, 2)) < this->attack_range 
		&& this->state == State::Move 
		&& this->attack_cooldown < 0)
	{
		move_val.x = 0.f;
		move_val.y = 0.f;
		this->state = State::Pre_Attack;
	}
	
	UpdateEffects(dt);
	UpdateFacingSide(target);

	if (this->state == State::Move)
	{
		this->entity.move(move_val * dt * speed);
	}
	

	

}

void Enemy::UpdateAttack(sf::Vector2f target, float dt, sf::RenderWindow& window)
{
	attack_cooldown -= dt;
	if (this->state == State::Pre_Attack && attack_cooldown < 0)
	{
		sf::Vector2f half_entity_size = GetGlobalBounds().getSize() / 2.f;
		sf::Vector2f start = sf::Vector2f(GetPosition().x + half_entity_size.x, GetPosition().y + half_entity_size.y);
		sf::Vector2f end = target;
		sf::Vector2f dir = end - start;

		float angle = std::atan2(dir.y, dir.x) * (180.f / 3.14159f);

		this->attack_box.setSize(sf::Vector2f(this->attack_range, GetGlobalBounds().getSize().x));
		this->attack_box.setOrigin(0.f, this->attack_box.getSize().y / 2.f);




		this->attack_box.setPosition(start);
		this->attack_box.setRotation(angle);
		this->attack_box.setFillColor(Enemy_Consts::attack_color);

		float angleRad = angle * (3.14159f / 180.f);
		sf::Vector2f direction(std::cos(angleRad), std::sin(angleRad));
		this->attack_target = start + direction * (this->attack_range + half_entity_size.x);

		this->time_until_attack = Enemy_Consts::attack_time_delay;
		this->state = State::Attack;
	} 
	else if (this->state == State::Attack)
	{
		time_until_attack -= dt;
		if (time_until_attack < 0)
		{
			if (current_dash_stage == 0)
			{
				sf::Vector2f direction_vector = this->attack_target - GetPosition();
				float direction_vector_length = std::sqrt(direction_vector.x * direction_vector.x + direction_vector.y * direction_vector.y);
				sf::Vector2f normalized_direction_vector = (direction_vector_length != 0.f)
					? direction_vector / direction_vector_length
					: sf::Vector2f(0.f, 0.f);
				dash_move_amount = (this->attack_range * normalized_direction_vector) - GetGlobalBounds().getSize() / 2.f;

				
				
			}
			this->dash_attack_time += dt;
			const float dash_stage_change_time = Enemy_Consts::default_dash_attack_time / Enemy_Consts::default_amount_dash_stages;
			sf::Vector2f splited_move_amount = dash_move_amount / static_cast<float>(Enemy_Consts::default_amount_dash_stages);
			if (this->dash_attack_time > dash_stage_change_time * this->current_dash_stage)
			{
				this->Entity::Move(splited_move_amount );
				entity.setColor(sf::Color(255, 255, 255, 75 + (180 / Enemy_Consts::default_amount_dash_stages) * current_dash_stage));
				current_dash_stage++;
			}
			else if (this->current_dash_stage == Enemy_Consts::default_amount_dash_stages)
			{
				this->attack_cooldown = Enemy_Consts::default_attack_cooldown;
				this->state = State::Stun;
				this->stun = Enemy_Consts::after_attack_stun;
				this->attack_box.setFillColor(sf::Color::Transparent);
				this->current_dash_stage = 0;
				this->dash_attack_time = 0;
				this->dash_move_amount = sf::Vector2f{ 0, 0 };
				entity.setColor(sf::Color(255, 255, 255, 255));
			}
			
		}
	}
}

void Enemy::UpdateFacingSide(sf::Vector2f target)
{
	if (this->state == State::Move)
	{
		if (this->entity.getPosition().x > target.x)
		{
			this->entity.setTextureRect(
				sf::IntRect(16, 0,
					-16,
					28
				));
			this->facing = Facing::Left;

		}
		else if (this->entity.getPosition().x < target.x)
		{
			this->entity.setTextureRect(
				sf::IntRect(0, 0,
					16,
					28
				));
			this->facing = Facing::Right;

		}
	}
}







