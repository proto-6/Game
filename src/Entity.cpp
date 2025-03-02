#include "Entity.h"

Entity::Entity()
	: hp(50.f), invincible(0.f), speed(300)
{
	this->entity.setPosition(-2000, -2000);
	this->entity.setOrigin(this->entity.getLocalBounds().width / 2.f, this->entity.getLocalBounds().height / 2.f);
}

void Entity::ReceiveDamage()
{
	if (invincible < 0.f)
	{
		this->hp -= 10;
		this->invincible = 0.5f;
		
	}
}

void Entity::UpdateEffectsDuration(float dt)
{
	invincible -= dt;
}


