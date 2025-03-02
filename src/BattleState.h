#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <random>

#include "HUD.h"
#include "State.h"
#include "GameData.h"
#include "Character.h"
#include "Enemy.h"
#include "Map.h"
#include "Timer.h"

class BattleState : public State
{
private:
    Map map;
    Timer timer;
    sf::View view;
    GameDataRef data;
    std::mt19937 rng;
    sf::Clock time_elapsed;
    HUD hud;

    // Entities
    float enemy_spawnrate;
    std::shared_ptr<Character> hero;
    std::vector<std::shared_ptr<Enemy>> enemies;

    // Methods
    void UpdateView(float dt);
    void DrawTimer();

    void UpdateEnemyPosition(float dt);
    void UpdateEnemyAnimation(float dt);
    void UpdateEffectsDuration(float dt);
    void DrawEnemy(float dt);
    
    void MapBordersCheck();
    void CheckCollisions();
public:
    BattleState(GameDataRef data, std::shared_ptr<Character> hero);

    // Initialization
    void Init() override;

    // Core methods
    void HandleInput(float dt) override;
    void Update(float dt) override;
    void Render(float dt) override;
};
