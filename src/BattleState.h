#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <random>

#include "State.h"
#include "GameData.h"
#include "Character.h"
#include "Enemy.h"
#include "Map.h"

class BattleState : public State
{
private:
	GameDataRef data;
	std::mt19937 rng;
	sf::Clock time_elapsed;
	float enemy_spawnrate;
	std::shared_ptr<Character> hero;
	std::vector<std::shared_ptr<Enemy>> enemies;
	sf::Vector2f velocity;
	

	Map map;
	sf::View view;

	// Methods
	void ProcessMovement(float dt);
	void UpdateView();

	// Enemies methods
	void UpdateEnemyPosition(float dt);
	void UpdateEnemyAnimation(float dt);
	void DrawEnemy(float dt);
public:
	BattleState(GameDataRef data, std::shared_ptr<Character> hero);


	// Initialization
	void Init() override;

	// Core methods
	void HandleInput(float dt) override;
	void Update(float dt) override;
	void Render(float dt) override;
};

