#pragma once
#include "GameData.h"

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Application.h"


class SplashState : public State
{
private:
	GameDataRef _data;
	sf::Clock _clock;

	sf::Sprite _logo;
	sf::Text _text;
public:
	SplashState(GameDataRef data);

	void Init();

	void HandleInput(float dt);
	void Update(float dt);
	void Render(float dt);

};

