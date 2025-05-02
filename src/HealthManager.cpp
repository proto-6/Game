#include "HealthManager.h"


void HealthManager::Lerp(float dt)
{
    sf::Vector2f current_hp_size = this->current_hp.getGlobalBounds().getSize();
    sf::Vector2f expected_size{ lost_hp.getGlobalBounds().getSize().x + (current_hp_size.x - lost_hp.getGlobalBounds().getSize().x) * dt, 30.f };
    if (expected_size.x < 300.f || expected_size.x > 300.f)
    {
        int a = 2 / 3;
    }
    this->lost_hp.setSize(sf::Vector2f(expected_size.x, expected_size.y));
}

HealthManager::HealthManager(AssetManager& assets, int& hp)
    : hp(hp)
{
    this->max_hp.setOutlineThickness(2.f);
    this->max_hp.setOutlineColor(sf::Color(218, 200, 200));
    this->max_hp.setPosition(50.f, SCREEN_HEIGHT / 16.f);
    this->max_hp.setSize(sf::Vector2f(this->hp * 3, 30.f));

    this->current_hp.setFillColor(sf::Color(0, 230, 0, 204));
    this->current_hp.setPosition(50.f, SCREEN_HEIGHT / 16.f);
    this->current_hp.setSize(sf::Vector2f(this->hp * 3, 30.f));

    this->lost_hp.setFillColor(sf::Color(255, 20, 20, 140));
    this->lost_hp.setPosition(50.f, SCREEN_HEIGHT / 16.f);
    this->lost_hp.setSize(sf::Vector2f(this->hp * 3, 30.f));


    //this->text.setPosition(this->text.getGlobalBounds().getSize().x / 2.f + 20.f, SCREEN_HEIGHT / 16.f);
}

void HealthManager::SetPosition(sf::Vector2f pos)
{
    this->max_hp.setPosition(pos);
    this->current_hp.setPosition(pos);
}

void HealthManager::Draw(sf::RenderWindow& window)
{
    window.draw(max_hp);
    window.draw(lost_hp);
    window.draw(current_hp);
}

void HealthManager::Update(float dt)
{
    this->current_hp.setSize(sf::Vector2f(hp * 3, this->current_hp.getGlobalBounds().getSize().y));
    Lerp(dt);
}

