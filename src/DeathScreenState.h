#pragma once
#include <SFML/Graphics.hpp>

#include "State.h"
#include "GameData.h"
#include "ScoreManager.h"
#include "Button.h"
#include "DEFINITIONS.h"

#include "MainMenuState.h"

class DeathScreenState : public State
{
private:
	sf::Text message;
	gm::Button button;
	ScoreManager score;
	GameDataRef data;

	ButtonName::Type hover_button_type;

public:
	DeathScreenState(GameDataRef data, ScoreManager score);

	void Init() override;

	void HandleInput(float dt) override;
	void Update(float dt) override;
	void Render(float dt) override;
};

