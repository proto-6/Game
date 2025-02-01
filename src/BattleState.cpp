#include "BattleState.h"
#include <iostream>


void BattleState::ProcessMovement(float dt)
{
	float zoom = 1.f;

	sf::Vector2f acceleration;

	// adjust this at will
	const float dAcc = 0.3f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		acceleration.x -= dAcc;
		this->hero->SetState(CharacterMovement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		acceleration.x += dAcc;
		this->hero->SetState(CharacterMovement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		acceleration.y -= dAcc;
		this->hero->SetState(CharacterMovement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		acceleration.y += dAcc;
		this->hero->SetState(CharacterMovement::State::Running);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		zoom = 3.5f;
	}

	velocity += acceleration;

	velocity = 0.95f * velocity;

	this->hero->Move(velocity);
}

void BattleState::UpdateEnemyPosition(float dt)
{
	for (auto& enemy : enemies)
	{
		enemy->UpdateMovement(this->hero->GetPosition(), dt);
	}
}

void BattleState::UpdateEnemyAnimation(float dt)
{
	for (auto& enemy : enemies)
	{
		enemy->UpdateAnimation(dt);
	}
}

void BattleState::DrawEnemy(float dt)
{
	for (auto& enemy : enemies)
	{
		enemy->Draw(&this->data->window, dt);
	}
}

void BattleState::UpdateView()
{
	const float half_view_x = this->view.getSize().x / 2.f;
	const float half_view_y = this->view.getSize().y / 2.f;
	sf::Vector2f view_center = sf::Vector2f(this->hero->GetPosition().x + this->hero->GetGlobalBounds().width / 2.f, this->hero->GetPosition().y);


	if (this->hero->GetPosition().x + half_view_x + this->hero->GetGlobalBounds().width / 2.f >= POSITIVE_BORDER_X)
		view_center.x = POSITIVE_BORDER_X - half_view_x;

	else if (this->hero->GetPosition().x - half_view_x + this->hero->GetGlobalBounds().width / 2.f  <= NEGATIVE_BORDER_X)
		view_center.x = NEGATIVE_BORDER_X + half_view_x;
	
	if (this->hero->GetPosition().y + half_view_y >= POSITIVE_BORDER_Y)
		view_center.y = POSITIVE_BORDER_Y - half_view_y;
	
	else if (this->hero->GetPosition().y - half_view_y <= NEGATIVE_BORDER_Y)
		view_center.y = NEGATIVE_BORDER_Y + half_view_y;

	view.setCenter(view_center);
	
	
}

BattleState::BattleState(GameDataRef data, std::shared_ptr<Character> hero)
	: data(data), hero(hero), rng(std::random_device{}())
{

}

void BattleState::Init()
{
	this->hero->SetScale(sf::Vector2f(4, 4)); // Size of character
	this->hero->SetPosition(0.f, 0.f);
	view.setCenter(0.f, 0.f);
	view.setSize(sf::Vector2f(1920, 1080));
	this->enemy_spawnrate = 2000.f;
	time_elapsed.restart();
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

	std::cout << time_elapsed.getElapsedTime().asMilliseconds() << std::endl;
	if (static_cast<unsigned int>(time_elapsed.getElapsedTime().asMilliseconds()) > this->enemies.size() * enemy_spawnrate)
	{
		this->enemies.push_back(std::make_shared<Enemy>(this->data->assets, rng));
	}

	this->hero->UpdateAnimation(dt);
	this->hero->ClearDirection();
	UpdateEnemyPosition(dt);
	UpdateEnemyAnimation(dt);
}

void BattleState::Render(float dt)
{
	this->data->window.clear(sf::Color(16, 16, 16));
	this->data->window.draw(map);
	this->hero->Draw(&this->data->window, dt);
	DrawEnemy(dt);
	UpdateView(); // It's here cause smoother camera movement
	this->data->window.setView(view); // Same ^
	

	this->data->window.display();
}
