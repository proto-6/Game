#pragma once
#include <SFML/Graphics.hpp>

class BaseAttack
{
protected:
	const float base_damage = 50.f;

	sf::RectangleShape hitbox;
public:
	BaseAttack(sf::Vector2f hitbox_size);

	bool CheckCollision(sf::FloatRect target_rect);
	float GetDamage() const { return this->base_damage; }

};

