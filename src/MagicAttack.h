#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "BaseAttack.h"

namespace MagicAttack_Consts {
	const float bigger_rect_rotation_speed = 2420.f;
	const float smaller_rect_rotation_speed = -2850.f;
};

class MagicAttack : public BaseAttack
{
private:
	// 2 rotational components that will be displayed as animation
	sf::RectangleShape bigget_rect;
	sf::RectangleShape smaller_rect;

	// Normalized direction vector
	sf::Vector2f direction;
	float speed;

	
public:
	MagicAttack() = delete;
	MagicAttack(sf::Vector2f start_pos, sf::Vector2f mouse_pos);

	// Getters
	sf::Vector2f GetPosition();
	sf::FloatRect GetGlobalBounds() { return this->hitbox.getGlobalBounds(); }

	// Setters
	void SetPosition(sf::Vector2f pos);
	void Move(sf::Vector2f move_val);

	void UpdateAnimation(float dt);
	void UpdateMovement(float dt);
	void Draw(sf::RenderWindow& window);
};

