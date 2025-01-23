#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "State.h"
#include "GameData.h"
#include "Character.h"
#include "Map.h"

class BattleState : public State
{
private:
	GameDataRef data;
	std::shared_ptr<Character> hero;
	Map map;
	sf::View view;

	// Methods
	void ProcessMovement(float dt);
	void UpdateView();
public:
	BattleState(GameDataRef data, std::shared_ptr<Character>& hero);


	// Initialization
	void Init() override;

	// Core methods
	void HandleInput(float dt) override;
	void Update(float dt) override;
	void Render(float dt) override;
};

