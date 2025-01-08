#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "State.h"
#include "GameData.h"
#include "Character.h"

class BattleState : public State
{
private:
	GameDataRef _data;
	std::shared_ptr<Character> _hero;
	sf::View view;

public:
	BattleState(GameDataRef data, std::shared_ptr<Character>& hero);

	// Initialization
	void Init() override;

	// Core methods
	void HandleInput() override;
	void Update(float dt) override;
	void Render(float dt) override;
};

