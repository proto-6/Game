#include "HealthManager.h"

std::string HealthManager::GetString()
{
    std::string text;
    
    text.append("Health: ");
    text.append(std::to_string(this->hp));
    
    return text;
}


HealthManager::HealthManager(AssetManager& assets, int& hp)
    : hp(hp)
{

    this->text.setFont(assets.GetFont(Font::PixeloidSans));
    this->text.setCharacterSize(42);
    this->text.setString(GetString());
    this->text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
    this->text.setPosition(this->text.getGlobalBounds().getSize().x / 2.f + 20.f, SCREEN_HEIGHT / 16.f);
}

void HealthManager::Draw(sf::RenderWindow& window)
{
    window.draw(text);
}

void HealthManager::ResetString()
{
    this->text.setString(this->GetString());
}
