#include "Entity.h"

Entity::Entity()
{
	this->entity.setOrigin(this->entity.getLocalBounds().width / 2.f, this->entity.getLocalBounds().height / 2.f);
}


