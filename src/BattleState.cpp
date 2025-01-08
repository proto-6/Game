#include "BattleState.h"

BattleState::BattleState(GameDataRef data, std::shared_ptr<Character>& hero) 
	: _data(data), _hero(hero) 
{

}

void BattleState::Init()
{
	_hero->SetScale(sf::Vector2f(3, 3)); // Size of character
	_hero->SetPosition // Center of screen
	(
		_data->window.getSize().x / 2.f,
		_data->window.getSize().y / 2.f
	);
	view.setCenter(sf::Vector2f(0, 0));
	view.setSize(sf::Vector2f(1920, 1080));
}

void BattleState::HandleInput()
{
	sf::Event ev;

	while (_data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) this->_data->window.close();


	}
}

void BattleState::Update(float dt)
{
	
	_hero->Update(dt);
	view.setCenter(_hero->GetPosition());
}

void BattleState::Render(float dt)
{
	this->_data->window.clear(sf::Color(16, 16, 16));
	this->_data->window.setView(view);
	_hero->Draw(&this->_data->window, dt);
	


	_data->window.display();
}
