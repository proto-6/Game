#pragma once
#include "GameData.h"
#include "DEFINITIONS.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

#include "StateStack.h"
#include "AssetManager.h"
#include "InputManager.h"



class Application
{
public:
	Application(int width, int heigh, std::string title);
	void Run();

private:
	// Variables
	const float dt = 1.f / 60.f;
	sf::Clock _clock;

	GameDataRef _data;

};

