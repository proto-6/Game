#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "State.h"
#include "Button.h"
#include "DEFINITIONS.h"
#include "GameMenuState.h"
#include "Character.h"

class MainMenuState : public State
{
private:
	GameDataRef _data;
	ButtonName::Type _hover_button_type;

	std::vector<gm::Button> _buttons;
	std::shared_ptr<Character> hero;
public:
	MainMenuState(GameDataRef data);


	// Misc
	void MoveCharacter(sf::Vector2f pos2, float dt);

	// Initializations
	void Init();
	void InitButtons();
	void InitCharacter();
	
	// Core methods
	void HandleInput();
	void Update(float dt);
	void UpdateButtons();
	void Render(float dt);

};

