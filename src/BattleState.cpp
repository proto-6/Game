#include "BattleState.h"


void BattleState::UpdateEnemy(float dt)
{
	for (auto& enemy : enemies)
	{
		enemy->UpdateMovement(this->hero->GetPosition(), dt);
		enemy->UpdateAnimation(dt);
		enemy->UpdateAttack(this->hero->GetPosition(), dt, this->data->window);
		
	}
}


void BattleState::UpdateEffectsDuration(float dt)
{
	this->hero->UpdateEffectsDuration(dt);

	for (auto& enemy : enemies)
	{
		enemy->UpdateEffectsDuration(dt);
	}
}

void BattleState::UpdateAfterDamageBlinking(float dt)
{
	if (this->character_blink > 0)
	{
		this->character_blink -= 1 * dt;
	}
}

void BattleState::DrawEnemy(float dt)
{
	for (auto& enemy : enemies)
	{
		enemy->Draw(&this->data->window, dt);
	}
}



void BattleState::MapBordersCheck()
{
	if (this->hero->GetGlobalBounds().getPosition().x < NEGATIVE_BORDER_X)
	{
		this->hero->SetPosition(NEGATIVE_BORDER_X + this->hero->GetGlobalBounds().width / 2.f, this->hero->GetPosition().y);
	}
	if (this->hero->GetGlobalBounds().getPosition().x + this->hero->GetGlobalBounds().width > POSITIVE_BORDER_X)
	{
		this->hero->SetPosition(POSITIVE_BORDER_X - this->hero->GetGlobalBounds().width / 2.f, this->hero->GetPosition().y);
	}
	if (this->hero->GetGlobalBounds().getPosition().y < NEGATIVE_BORDER_Y)
	{
		this->hero->SetPosition(this->hero->GetPosition().x, NEGATIVE_BORDER_Y + this->hero->GetGlobalBounds().height / 2.f);
	}
	if (this->hero->GetGlobalBounds().getPosition().y + this->hero->GetGlobalBounds().height > POSITIVE_BORDER_Y)
	{
		this->hero->SetPosition(this->hero->GetPosition().x, POSITIVE_BORDER_Y - this->hero->GetGlobalBounds().height / 2.f);
	}
}

void BattleState::CheckCollisions()
{
	for (auto it = this->enemies.begin(); it != this->enemies.end(); )
	{
		auto& enemy = *it;
		sf::FloatRect hero_collision_box = this->hero->GetGlobalBounds();
		if (hero_collision_box.intersects(enemy->GetGlobalBounds()))
		{
			this->hero->ReceiveDamage(*enemy);
			if (!(this->character_blink > 0.f))
			{
				this->character_blink = 0.5f;
			}
		}
		if (this->hero->IsAttackUsed())
		{
			sf::FloatRect attack_collision_box = this->hero->GetAttackCollisionBox();
			if (attack_collision_box.intersects(enemy->GetGlobalBounds()))
			{
				enemy->ReceiveDamage(this->hero->GetAttackDamage());
				if (!enemy->IsAlive())
				{
					it = this->enemies.erase(it);
					this->hud.AddToScore();
					continue; // Skip incrementing, since erase already returns next valid iterator
				}
			}
		}
		

		++it; // Move to next enemy
	}
	
}

void BattleState::UpdateView(float dt)
{
	const float half_view_x = this->view.getSize().x / 2.f;
	const float half_view_y = this->view.getSize().y / 2.f;
	sf::Vector2f view_center = sf::Vector2f(this->hero->GetPosition().x, this->hero->GetPosition().y);
	sf::Vector2f movement = view_center - this->view.getCenter();

	

	if (std::abs(movement.x) < 2.f)
		movement.x = 0.f;
	if (std::abs(movement.y) < 2.f)
		movement.y = 0.f;

	view.move(movement * dt * 10.f);


}

BattleState::BattleState(GameDataRef data, std::shared_ptr<Character> hero)
	: data(data), hero(hero), rng(std::random_device{}()), enemy_spawnrate(0.f), map(data->window.getSize()), hud(this->data->assets, hero->GetHealth()), character_blink(0.f)
{
	
}

void BattleState::Init()
{
	this->hero->SetScale(sf::Vector2f(4, 4)); // So character isn't very small
	hero->SetOrigin(hero->GetLocalBounds().width / 2.f, hero->GetLocalBounds().height / 2.f); // So it's easier to centralize character
	this->hero->SetPosition(0.f, 0.f);
	hero->SetState(CharacterMovement::State::Idle);

	view.setCenter(0.f, 0.f);
	view.setSize(sf::Vector2f(1920, 1080));
	this->enemy_spawnrate = 4000.f;
	time_elapsed.restart();

	this->shader.loadFromFile("DamageReceiveShader.frag", sf::Shader::Fragment);
	this->shader.setUniform("flash_color", sf::Glsl::Vec4(0.7f, 0.f, 0.f, 0.1f));
	this->character_blink = 0.f;


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
	this->hud.Update();
	UpdateView(dt);
	this->hero->UpdateMovement(dt);
	this->MapBordersCheck();

	if (static_cast<unsigned int>(time_elapsed.getElapsedTime().asMilliseconds()) > this->enemies.size() * enemy_spawnrate)
	{
		this->enemies.push_back(std::make_shared<Enemy>(this->data->assets, rng));
	}

	this->hero->UpdateAnimation(dt);
	this->hero->ClearDirection();
	this->hero->UpdateAttack(dt, this->data->window, map.GetGlobalBounds());
	UpdateEnemy(dt);
	CheckCollisions();
	UpdateEffectsDuration(dt);
	UpdateAfterDamageBlinking(dt);
	this->shader.setUniform("flash_color", sf::Glsl::Vec4(0.7f, 0.f, 0.f, this->character_blink));
}

void BattleState::Render(float dt)
{
	this->data->window.clear(sf::Color(16, 16, 16));
	this->data->window.draw(map);
	this->hero->Draw(&this->data->window, shader, dt);
	DrawEnemy(dt);
	if (this->hero->IsAttackUsed())
	{
		this->hero->DrawAttack(&this->data->window);
	}

	hud.Draw(this->data->window, this->view);
	
	this->data->window.display();
}

