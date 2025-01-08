#include "Character.h"
#include "DEFINITIONS.h"


Character::Character(AssetManager& manager)
{
	
	// Loading character idle animations into asset manager and adding it into an array so we can switch textures as we go
	manager.LoadTexture(Texture::CharacterIdle0, "../resource/assets/character/wizzard_m_idle_anim_f0.png");
	_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle0)));

	manager.LoadTexture(Texture::CharacterIdle1, "../resource/assets/character/wizzard_m_idle_anim_f1.png");
	_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle1)));

	manager.LoadTexture(Texture::CharacterIdle2, "../resource/assets/character/wizzard_m_idle_anim_f2.png");
	_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle2)));

	manager.LoadTexture(Texture::CharacterIdle3, "../resource/assets/character/wizzard_m_idle_anim_f3.png");
	_animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle3)));
	
	// Setting initial texture to a character
	_hero.setTexture(*_animations[0]);
	_current_animation = 0;
	_state = Character::State::Idle;

	_hero.setPosition(sf::Vector2f(0, 0));
	_animation_interval = 0.2f;
	_elapsed_time = 0.f;
	_hero.setScale(20, 20);
}

Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		this->_animations = other._animations;
		this->_current_animation = other._current_animation;
		this->_hero = other._hero;
		this->_state = other._state;
	}
	return *this;
}


sf::Vector2f Character::GetScale() const
{
	return _hero.getScale();
}

void Character::Draw(sf::RenderWindow* window, float dt)
{
	window->draw(_hero);
}

void Character::Update(float dt)
{
	_elapsed_time += dt;
	if (_elapsed_time >= _animation_interval)
	{
		_elapsed_time -= _animation_interval;

		switch (_state)
		{
		case Character::State::Idle:
			
			_current_animation = (_current_animation + 1) % _animations.size(); // So vector doesn't overflow

			_hero.setTexture(*_animations[_current_animation]); // Set hero texture to next one
			break;
		default:
			break;
		}
	}
}

void Character::SetPosition(sf::Vector2f pos2)
{
	_hero.setPosition(pos2);
}

void Character::SetPosition(float x, float y)
{
	_hero.setPosition(x, y);
}

void Character::SetScale(sf::Vector2f scale)
{
	_hero.setScale(scale);
}




