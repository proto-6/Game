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
	sf::CircleShape circle;

	// Methods
	void ProcessMovement(float dt);

public:
	BattleState(GameDataRef data, std::shared_ptr<Character>& hero);

	// Initialization
	void Init() override;

	// Core methods
	void HandleInput(float dt) override;
	void Update(float dt) override;
	void Render(float dt) override;
};

