#pragma once
#include "DEFINITIONS.h"

#include "GameData.h"

#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.h"




namespace gm 
{
class Button : public sf::Drawable
{
private:
	sf::Text _text;
	sf::RoundedRectangleShape _rectangle;
	sf::Vector2f original_size;
	sf::Vector2f original_position;

	void CentralizeText();
	void CentralizeTextOrigin();
	sf::Vector2f Lerp(sf::Vector2f& pos_original, sf::Vector2f& pos_expected, float speed)
	{
		return pos_original + speed * (pos_expected - pos_original);
	}
public:
	Button(sf::String text);

	// Setters
	void SetSize(const sf::Vector2f& size);
	void SetPosition(sf::Vector2f pos);
	void SetPosition(float x, float y);
	void SetFont(Font::Type font, GameDataRef _data);
	void SetCornerPointCount(unsigned int count);
	void SetCornerRadius(float radius);
	void SetOrigin(sf::Vector2f coords);

	// Getters
	const sf::Vector2f& GetSize();
	const sf::Vector2f& GetPosition();
	unsigned int GetCornerPointCount();
	float GetCornerRadius();
	sf::FloatRect GetGlobalBounds();
	sf::Vector2f GetOrigin();

	ButtonName::Type GetButtonType();

	void Hover(sf::Vector2f expected, sf::Vector2i mouse_pos, float speed);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
}



