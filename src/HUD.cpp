#include "HUD.h"

HUD::HUD(AssetManager& assets, HealthManager hp, Score::Type type)
	: timer(assets), hp(hp), score(assets, type)
{
	
	
}

void HUD::Draw(sf::RenderWindow& target, sf::View& view)
{
	target.setView(target.getDefaultView());
	this->hp.Draw(target);
	this->timer.Draw(target);
	score.Draw(target);

	target.setView(view);
}

void HUD::Update(float dt)
{
	this->timer.Update();

	this->hp.Update(dt);

}


void HUD::AddToScore()
{
	this->score.AddToScore(100);
}
