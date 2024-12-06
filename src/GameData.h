#pragma once
#include "StateStack.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "AssetManager.h"
#include "InputManager.h"

struct GameData
{
	StateStack stack;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
};

using GameDataRef = std::shared_ptr<GameData>;