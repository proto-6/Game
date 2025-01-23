#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "State.h"
#include "GameData.h"
#include "Character.h"
#include "Enemy.h"
#include "Map.h"

class BattleState : public State
{
private:
	GameDataRef data;
	std::shared_ptr<Character> hero;
	std::vector<std::shared_ptr<Enemy>> enemies;

	Map map;
	sf::View view;

	// Methods
	void ProcessMovement(float dt);
	void UpdateView();
public:
	BattleState(GameDataRef data, std::shared_ptr<Character> hero);


	// Initialization
	void Init() override;

	// Core methods
	void HandleInput(float dt) override;
	void Update(float dt) override;
	void Render(float dt) override;
};

