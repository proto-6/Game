#include "Character.h"
#include "DEFINITIONS.h"


Character::Character(AssetManager& manager)
{
	LoadAnimations(manager);
	

	_hero.setPosition(sf::Vector2f(0, 0));
	_animation_interval = 0.2f;
	_elapsed_time = 0.f;
	_hero.setScale(1, 1);
	_direction.x = 0.f;
	_direction.y = 0.f;
	_speed = 200.f;
}

Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		this->_idle_animations = other._idle_animations;
		this->_run_animations = other._run_animations;
		this->_current_animation = other._current_animation;
		this->_hero = other._hero;
		this->_state = other._state;
	}
	return *this;
}

void Character::LoadAnimations(AssetManager& manager)
{
	// Loading character idle animations into asset manager and adding it into an array so we can switch textures as we go
	// Idle animations
	manager.LoadTexture(Texture::CharacterIdle0, "../resource/assets/character/wizzard_m_idle_anim_f0.png");
	_idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle0)));
	manager.LoadTexture(Texture::CharacterIdle1, "../resource/assets/character/wizzard_m_idle_anim_f1.png");
	_idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle1)));
	manager.LoadTexture(Texture::CharacterIdle2, "../resource/assets/character/wizzard_m_idle_anim_f2.png");
	_idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle2)));
	manager.LoadTexture(Texture::CharacterIdle3, "../resource/assets/character/wizzard_m_idle_anim_f3.png");
	_idle_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle3)));

	// Run animations
	manager.LoadTexture(Texture::CharacterRun0, "../resource/assets/character/wizzard_m_run_anim_f0.png");
	_run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterRun0)));
	manager.LoadTexture(Texture::CharacterRun1, "../resource/assets/character/wizzard_m_run_anim_f1.png");
	_run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterRun1)));
	manager.LoadTexture(Texture::CharacterRun2, "../resource/assets/character/wizzard_m_run_anim_f2.png");
	_run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterRun2)));
	manager.LoadTexture(Texture::CharacterRun3, "../resource/assets/character/wizzard_m_run_anim_f3.png");
	_run_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterRun3)));

	// Setting initial texture to a character
	_current_animation = 0;
	_hero.setTexture(*_idle_animations[_current_animation]);
	_state = Movement::State::Idle;
}


sf::Vector2f Character::GetScale() const
{
	return this->_hero.getScale();
}

sf::Vector2f Character::GetDirection()
{
	return this->_direction;
}

Movement::State Character::GetState() const
{
	return this->_state;
}

float Character::GetSpeed()
{
	return this->_speed;
}

void Character::Draw(sf::RenderWindow* window, float dt)
{
	window->draw(this->_hero);
}

#include <iostream>

void Character::Update(float dt)
{
	if (this->_state == Movement::State::Running)
	{
		_elapsed_time += dt / 1.8f;
	}
	_elapsed_time += dt / 1.5;
	if (_elapsed_time >= _animation_interval)
	{
		_elapsed_time -= _animation_interval;

		switch (_state)
		{
		case Movement::State::Idle:
			std::cout << "Idle" << std::endl;
			_current_animation = (_current_animation + 1) % _idle_animations.size(); // So vector doesn't overflow

			this->_hero.setTexture(*_idle_animations[_current_animation]); // Set hero texture to next one
			break;
		case Movement::State::Running:
			std::cout << "Running" << std::endl;
			_current_animation = (_current_animation + 1) % _run_animations.size(); // So vector doesn't overflow

			this->_hero.setTexture(*_run_animations[_current_animation]); // Set hero texture to next one
			break;
			
		default:
			break;
		}
	}
}

void Character::SetPosition(sf::Vector2f pos2)
{
	this->_hero.setPosition(pos2);
}

void Character::SetPosition(float x, float y)
{
	this->_hero.setPosition(x, y);
}

void Character::Move(sf::Vector2f pos2)
{
	this->_hero.move(pos2);
}

void Character::Move(float x, float y)
{
	this->_hero.move(x, y);
}

void Character::SetScale(sf::Vector2f scale)
{
	_hero.setScale(scale);
}

void Character::SetScale(float x, float y)
{
	_hero.setScale(x, y);
}

void Character::SetSpeed(float speed)
{
	_speed = speed;
}

void Character::SetDirection(float x, float y)
{
	this->_direction.x += x;
	this->_direction.y += y;
}

void Character::SetDirection(sf::Vector2f direction)
{
	this->_direction.x += direction.x;
	this->_direction.y += direction.y;
}

void Character::ClearDirection()
{
	this->_direction.x = 0.f;
	this->_direction.y = 0.f;
	this->_state = Movement::State::Idle;
}

void Character::SetState(Movement::State state)
{
	this->_state = state;
}







