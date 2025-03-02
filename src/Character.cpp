#include "Character.h"
#include "DEFINITIONS.h"


Character::Character(AssetManager& manager)
{
	LoadAnimations(manager);
	
	
	entity.setPosition(sf::Vector2f(0, 0));
	animation_interval = 0.2f;
	elapsed_time = 0.f;
	entity.setScale(1, 1);
	velocity.x = 0.f;
	velocity.y = 0.f;
	speed = 500.f;
}

Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		this->idle_animations = other.idle_animations;
		this->run_animations = other.run_animations;
		this->current_animation = other.current_animation;
		this->entity = other.entity;
		this->state = other.state;
	}
	return *this;
}

void Character::LoadAnimations(AssetManager& manager)
{
	// Loading character idle animations into asset manager and adding it into an array so we can switch textures as we go
	// Idle animations
	manager.LoadTexture(Texture::CharacterIdle0, "../resource/assets/character/wizzard_m_idle_anim_f0.png");
	idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle0)));
	manager.LoadTexture(Texture::CharacterIdle1, "../resource/assets/character/wizzard_m_idle_anim_f1.png");
	idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle1)));
	manager.LoadTexture(Texture::CharacterIdle2, "../resource/assets/character/wizzard_m_idle_anim_f2.png");
	idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle2)));
	manager.LoadTexture(Texture::CharacterIdle3, "../resource/assets/character/wizzard_m_idle_anim_f3.png");
	idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle3)));

	// Run animations
	manager.LoadTexture(Texture::CharacterRun0, "../resource/assets/character/wizzard_m_run_anim_f0.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterRun0)));
	manager.LoadTexture(Texture::CharacterRun1, "../resource/assets/character/wizzard_m_run_anim_f1.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterRun1)));
	manager.LoadTexture(Texture::CharacterRun2, "../resource/assets/character/wizzard_m_run_anim_f2.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterRun2)));
	manager.LoadTexture(Texture::CharacterRun3, "../resource/assets/character/wizzard_m_run_anim_f3.png");
	run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterRun3)));

	// Setting initial texture to a character
	current_animation = 0;
	entity.setTexture(*idle_animations[current_animation]);
	state = CharacterMovement::State::Idle;
}




void Character::UpdateAnimation(float dt)
{
	if (this->state == CharacterMovement::State::Running)
	{
		elapsed_time += dt * this->speed / 800.f;
	}
	elapsed_time += dt / 1.5f;
	if (elapsed_time >= animation_interval)
	{
		elapsed_time -= animation_interval;

		switch (state)
		{
		case CharacterMovement::State::Idle:
			current_animation = (current_animation + 1) % idle_animations.size(); // So vector doesn't overflow

			this->entity.setTexture(*idle_animations[current_animation]); // Set entity texture to next one
			break;
		case CharacterMovement::State::Running:
			current_animation = (current_animation + 1) % run_animations.size(); // So vector doesn't overflow

			this->entity.setTexture(*run_animations[current_animation]); // Set entity texture to next one
			break;
			
		default:
			break;
		}
	}
}

void Character::UpdateMovement(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->velocity.x += -this->speed * dt;
		SetState(CharacterMovement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->velocity.x += this->speed * dt;
		SetState(CharacterMovement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->velocity.y += -this->speed * dt;
		SetState(CharacterMovement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->velocity.y += this->speed * dt;
		SetState(CharacterMovement::State::Running);
	}
	if (static_cast<int>(velocity.x) == 0 && static_cast<int>(velocity.y) == 0)
	{
		SetState(CharacterMovement::State::Idle);
	}

	if (static_cast<int>(velocity.x) != 0 && static_cast<int>(velocity.y) != 0)
	{
		this->velocity.x /= std::sqrt(2);
		this->velocity.y /= std::sqrt(2);
	}

	Move(this->velocity);
}

void Character::SetDirection(float x, float y)
{
	this->velocity.x += x;
	this->velocity.y += y;
}

void Character::SetDirection(sf::Vector2f direction)
{
	this->velocity.x += direction.x;
	this->velocity.y += direction.y;
}

void Character::ClearDirection()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
	this->state = CharacterMovement::State::Idle;
}

