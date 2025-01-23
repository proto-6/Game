#include "BattleState.h"
#include <iostream>

void BattleState::ProcessMovement(float dt)
{
	float zoom = 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->hero->SetDirection(this->hero->GetPosition().x <= NEGATIVE_BORDER_X ? 0 : -1, 0);
		this->hero->SetState(Movement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->hero->SetDirection(this->hero->GetPosition().x >= POSITIVE_BORDER_X - this->hero->GetGlobalBounds().width ? 0 : 1, 0);
		this->hero->SetState(Movement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->hero->SetDirection(0, this->hero->GetPosition().y <= NEGATIVE_BORDER_Y - 24  ? 0 : -1); // ??? need to research this issue later (for later me -> I'm writing about "magical number")
		this->hero->SetState(Movement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->hero->SetDirection(0, this->hero->GetPosition().y >= POSITIVE_BORDER_Y - this->hero->GetGlobalBounds().height ? 0 : 1);
		this->hero->SetState(Movement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		zoom = 3.5f;
	}

	

	double direction_x = this->hero->GetDirection().x;
	double direction_y = this->hero->GetDirection().y;
	
	if (direction_x != 0. && direction_y != 0.)
	{
		direction_x /= std::sqrt(2);
		direction_y /= std::sqrt(2);
	}
	

	
	this->hero->Move(static_cast<float>(direction_x) * dt * this->hero->GetSpeed() * zoom, static_cast<float>(direction_y) * dt * this->hero->GetSpeed() * zoom);
	
	
	if (direction_x == 0 && direction_y == 0)
	{
		this->hero->SetState(Movement::State::Idle);
	}
}

void BattleState::UpdateView()
{
	const float half_view_x = this->view.getSize().x / 2.f;
	const float half_view_y = this->view.getSize().y / 2.f;
	sf::Vector2f view_center = sf::Vector2f(this->hero->GetPosition().x + this->hero->GetGlobalBounds().width / 2.f, this->hero->GetPosition().y);


	if (this->hero->GetPosition().x + half_view_x >= POSITIVE_BORDER_X)
		view_center.x = POSITIVE_BORDER_X - half_view_x;

	else if (this->hero->GetPosition().x - half_view_x <= NEGATIVE_BORDER_X)
		view_center.x = NEGATIVE_BORDER_X + half_view_x;
	
	if (this->hero->GetPosition().y + half_view_y >= POSITIVE_BORDER_Y)
		view_center.y = POSITIVE_BORDER_Y - half_view_y;
	
	else if (this->hero->GetPosition().y - half_view_y <= NEGATIVE_BORDER_Y)
		view_center.y = NEGATIVE_BORDER_Y + half_view_y;

	view.setCenter(view_center);
	
	
}

BattleState::BattleState(GameDataRef data, std::shared_ptr<Character>& hero)
	: data(data), hero(hero) 
{

}

void BattleState::Init()
{
	this->hero->SetScale(sf::Vector2f(4, 4)); // Size of character
	this->hero->SetPosition(0.f, 0.f);
	view.setCenter(0.f, 0.f);
	view.setSize(sf::Vector2f(1920, 1080));
	 
	map.LoadTiles(this->data->window.getSize());
}

void BattleState::HandleInput(float dt)
{
	sf::Event ev;

	while (this->data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) this->data->window.close();	
	}
}

void BattleState::Update(float dt)
{
	this->ProcessMovement(dt);
	this->hero->Update(dt);
	this->hero->ClearDirection();
	
}

void BattleState::Render(float dt)
{
	this->data->window.clear(sf::Color(16, 16, 16));
	this->data->window.draw(map);
	UpdateView();
	this->data->window.setView(view);
	this->hero->Draw(&this->data->window, dt);
	
	

	this->data->window.display();
}
