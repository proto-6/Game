#include "ScoreManager.h"

std::string ScoreManager::GetString()
{
    std::string text;

    text.append("Score: ");
    text.append(std::to_string(this->score));

    return text;
}

ScoreManager::ScoreManager(AssetManager& assets)
{
    this->score = 0;

    this->text.setFont(assets.GetFont(Font::PixeloidSans));
    this->text.setCharacterSize(42);
    this->text.setString(GetString());
    this->text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
    this->text.setPosition(SCREEN_WIDTH - 240.f, SCREEN_HEIGHT / 16.f);
}

void ScoreManager::SetScore(int new_score)
{
    this->score = new_score;
    this->text.setString(GetString());
}

void ScoreManager::AddToScore(int add_val)
{
    this->score += add_val;
    this->text.setString(GetString());
}

void ScoreManager::Draw(sf::RenderWindow& window)
{
    window.draw(this->text);
}
