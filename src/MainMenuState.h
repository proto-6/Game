#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "State.h"
#include "Button.h"
#include "DEFINITIONS.h"
#include "GameMenuState.h"
#include "Character.h"
#include "BattleState.h"

class MainMenuState : public State
{
private:
	GameDataRef _data;
	ButtonName::Type _hover_button_type;

	std::vector<gm::Button> _buttons;
	std::shared_ptr<Character> _hero;
public:
	MainMenuState(GameDataRef data);


	// Misc
	void MoveCharacter(sf::Vector2f pos2, float dt);

	// Initializations
	void Init() override;
	void InitButtons();
	void InitCharacter();
	
	// Core methods
	void HandleInput(float dt);
	void Update(float dt) override;
	void UpdateButtons();
	void Render(float dt) override;

};

