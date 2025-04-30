#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "AssetManager.h"

class Timer
{
private:
    sf::Clock clock;
    sf::Text text;

    // Methods
    std::string GetString();
public:
    Timer() = delete;
    Timer(AssetManager& assets);

    void Update();
    void Draw(sf::RenderWindow& window);
};
