#include "MagicAttack.h"

MagicAttack::MagicAttack(sf::Vector2f start_pos, sf::Vector2f mouse_pos) : BaseAttack(sf::Vector2f(30.f, 30.f)) {
	this->bigget_rect.setSize(sf::Vector2f(36.f, 24.f));
	this->bigget_rect.setOrigin(this->bigget_rect.getSize() / 2.f);
	this->bigget_rect.setFillColor(sf::Color(242, 242, 222));

	this->smaller_rect.setSize(sf::Vector2f(18.f, 6.f));
	this->smaller_rect.setOrigin(this->smaller_rect.getSize() / 2.f);
	this->smaller_rect.setFillColor(sf::Color(217, 217, 217, 210));

	sf::Vector2f direction_vector = mouse_pos - start_pos;
	float length = std::sqrt(direction_vector.x * direction_vector.x + direction_vector.y * direction_vector.y);
	this->direction = direction_vector / length;
	this->speed = 450.f;

	SetPosition(start_pos);
}

sf::Vector2f MagicAttack::GetPosition()
{
	return bigget_rect.getPosition();
}

void MagicAttack::SetPosition(sf::Vector2f pos)
{
	this->bigget_rect.setPosition(pos);
	this->smaller_rect.setPosition(pos);
	this->hitbox.setPosition(pos - this->hitbox.getSize() / 2.f);
}

void MagicAttack::Move(sf::Vector2f move_val)
{
	this->bigget_rect.setPosition(this->bigget_rect.getPosition() + move_val);
	this->smaller_rect.setPosition(this->smaller_rect.getPosition() + move_val);
	this->hitbox.setPosition(this->hitbox.getPosition() + move_val - this->hitbox.getSize() / 2.f);
}

void MagicAttack::UpdateAnimation(float dt)
{
	this->bigget_rect.rotate(dt * MagicAttack_Consts::bigger_rect_rotation_speed);
	this->smaller_rect.rotate(dt * MagicAttack_Consts::smaller_rect_rotation_speed);
}

void MagicAttack::UpdateMovement(float dt)
{
	SetPosition(GetPosition() + direction * speed * dt);
}

void MagicAttack::Draw(sf::RenderWindow& window)
{
	window.draw(this->bigget_rect);
	window.draw(this->smaller_rect);
}


