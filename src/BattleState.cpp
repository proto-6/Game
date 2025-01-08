#include "BattleState.h"
#include <iostream>

void BattleState::ProcessMovement(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->_hero->SetDirection(-1, 0);
		this->_hero->SetState(Movement::State::Moving);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->_hero->SetDirection(1, 0);
		this->_hero->SetState(Movement::State::Moving);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->_hero->SetDirection(0, -1);
		this->_hero->SetState(Movement::State::Moving);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->_hero->SetDirection(0, 1);
		this->_hero->SetState(Movement::State::Moving);
	}

	double direction_x = this->_hero->GetDirection().x;
	double direction_y = this->_hero->GetDirection().y;
	
	if (direction_x != 0. && direction_y != 0.)
	{
		direction_x /= std::sqrt(2);
		direction_y /= std::sqrt(2);
	}
	this->_hero->Move(direction_x * dt * this->_hero->GetSpeed(), direction_y * dt * this->_hero->GetSpeed());
	if (direction_x == 0 && direction_y)
	{
		this->_hero->SetState(Movement::State::Idle);
	}
}

BattleState::BattleState(GameDataRef data, std::shared_ptr<Character>& hero)
	: _data(data), _hero(hero) 
{

}

void BattleState::Init()
{
	this->_hero->SetScale(sf::Vector2f(3, 3)); // Size of character
	this->_hero->SetPosition // Center of screen
	(
		_data->window.getSize().x / 2.f,
		_data->window.getSize().y / 2.f
	);
	view.setCenter(0.f, 0.f);
	view.setSize(sf::Vector2f(1920, 1080));
	 
	circle.setRadius(100);
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(this->_hero->GetPosition());
}

void BattleState::HandleInput(float dt)
{
	sf::Event ev;

	while (this->_data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) this->_data->window.close();	
	}
}

void BattleState::Update(float dt)
{
	
	this->_hero->Update(dt);
	this->ProcessMovement(dt);
	this->_hero->ClearDirection();
	view.setCenter(this->_hero->GetPosition());
}

void BattleState::Render(float dt)
{
	this->_data->window.clear(sf::Color(16, 16, 16));
	this->_data->window.draw(circle);
	this->_data->window.setView(view);
	this->_hero->Draw(&this->_data->window, dt);
	


	this->_data->window.display();
}
