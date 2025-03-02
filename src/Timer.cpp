#include "Timer.h"

std::string Timer::GetString()
{
    std::string text;
    int minutes = static_cast<int>(clock.getElapsedTime().asSeconds()) / 60;
    int seconds = static_cast<int>(clock.getElapsedTime().asSeconds()) % 60;
    if (minutes < 1)
    {
        text.append("0:");
    }
    else
    {
        text.append(std::to_string(minutes) + ":");
    }

    if (seconds == 0)
    {
        text.append("00");
    }
    else if (seconds < 10)
    {
        text.append("0" + std::to_string(seconds));
    }
    else
    {
        text.append(std::to_string(seconds));
    }
    return text;
}

Timer::Timer(AssetManager& assets)
{
    this->clock.restart();
    this->text.setFont(assets.GetFont(Font::PixeloidSans));
    this->text.setCharacterSize(48);
    this->text.setString("0:00");
    this->text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
    this->text.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 16.f);
}

void Timer::Update()
{
    this->text.setString(GetString());
}

void Timer::Draw(sf::RenderWindow& window)
{
    window.draw(this->text);
}