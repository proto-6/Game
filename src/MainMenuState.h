#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "State.h"
#include "Button.h"
#include "DEFINITIONS.h"
#include "Character.h"
#include "BattleState.h"

class MainMenuState : public State
{
private:
	GameDataRef data;
	ButtonName::Type hover_button_type;
	std::vector<gm::Button> buttons;
	std::shared_ptr<Character> hero;

	ScoreManager hi_score;
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

