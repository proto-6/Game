#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "State.h"
#include "Button.h"
#include "DEFINITIONS.h"

class GameMenuState : public State
{
private:
	GameDataRef data;
	ButtonName::Type _hover_button_type;

	std::vector<gm::Button> _buttons;
	sf::Sprite _background;
public:

	GameMenuState(GameDataRef data);

	void Init() override;



	void HandleInput(float dt) override;
	void Update(float dt) override;
	void Render(float dt) override;

};

