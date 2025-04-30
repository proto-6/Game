#include "BaseAttack.h"

BaseAttack::BaseAttack(sf::Vector2f hitbox_size)
{
	this->hitbox.setSize(sf::Vector2f(hitbox_size));
}

bool BaseAttack::CheckCollision(sf::FloatRect target_rect)
{
	sf::FloatRect rect1 = hitbox.getGlobalBounds();
	if (rect1.intersects(target_rect))
	{
		return true;
	}
	return false;
}
