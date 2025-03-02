#include "HUD.h"

HUD::HUD(AssetManager& assets, Timer& timer, float& hp)
	: timer(timer), hp(hp) 
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << hp;
	this->hp_text.setFont(assets.GetFont(Font::PixeloidSans));
	this->hp_text.setCharacterSize(32);
	this->hp_text.setString(stream.str());
	this->hp_text.setOrigin(this->hp_text.getGlobalBounds().getSize() / 2.f + this->hp_text.getLocalBounds().getPosition());
	this->hp_text.setPosition(80, 50);
}

void HUD::Draw(sf::RenderWindow& target, sf::View& view)
{
	target.setView(target.getDefaultView());

	this->timer.Draw(target);
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << hp;
	this->hp_text.setString(stream.str());
	target.draw(hp_text);

	target.setView(view);
}
