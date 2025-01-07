#include "Character.h"
#include "DEFINITIONS.h"


Character::Character(AssetManager& manager)
{
	
	// Loading character idle animations into asset manager and adding it into an array so we can switch textures as we go
	manager.LoadTexture(Texture::CharacterIdle0, "../resource/assets/character/wizzard_m_idle_anim_f0.png");
	animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle0)));

	manager.LoadTexture(Texture::CharacterIdle1, "../resource/assets/character/wizzard_m_idle_anim_f1.png");
	animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle1)));

	manager.LoadTexture(Texture::CharacterIdle2, "../resource/assets/character/wizzard_m_idle_anim_f2.png");
	animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle2)));

	manager.LoadTexture(Texture::CharacterIdle3, "../resource/assets/character/wizzard_m_idle_anim_f3.png");
	animations.push_back(std::make_shared<sf::Texture>(manager.GetTexture(Texture::CharacterIdle3)));
	
	// Setting initial texture to a character
	hero.setTexture(*animations[0]);
	current_animation = 0;
	state = Character::State::Idle;

	hero.setPosition(sf::Vector2f(0, 0));
	animation_interval = 50.f;
	elapsed_time = 0.f;
	hero.setScale(20, 20);
}

Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		this->animations = other.animations;
		this->current_animation = other.current_animation;
		this->hero = other.hero;
		this->state = other.state;
	}
	return *this;
}


void Character::Draw(sf::RenderWindow* window, float dt)
{
	window->draw(hero);
}

void Character::Update(float dt)
{
	elapsed_time += dt;
	if (elapsed_time >= animation_interval)
	{
		elapsed_time -= animation_interval;

		switch (state)
		{
		case Character::State::Idle:
			
			current_animation = (current_animation + 1) % animations.size(); // So vector doesn't overflow

			hero.setTexture(*animations[current_animation]); // Set hero texture to next one
			break;
		default:
			break;
		}
	}
}

void Character::SetPosition(sf::Vector2f& pos2)
{
	hero.setPosition(pos2);
}




