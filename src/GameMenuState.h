#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "State.h"
#include "Button.h"
#include "DEFINITIONS.h"

class GameMenuState : public State
{
private:
	GameDataRef _data;
	ButtonName::Type _hover_button_type;

	std::vector<gm::Button> _buttons;
	sf::Sprite _background;
public:

	GameMenuState(GameDataRef data);

	void Init();



	void HandleInput();
	void Update(float dt);
	void Render(float dt);

};

