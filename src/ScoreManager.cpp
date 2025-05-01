#include "ScoreManager.h"

std::string ScoreManager::GetString()
{
    std::string text;
    if (this->type == Score::Type::In_Game)
    {
        text.append("Score: ");
        text.append(std::to_string(this->score));
    }
    else if (this->type == Score::Type::Hi_Score)
    {
        text.append("HI-Score: ");
        LoadScoreFromFile();
        text.append(std::to_string(this->score));
    }

    

    return text;
}

ScoreManager::ScoreManager(AssetManager& assets, Score::Type type)
    : type(type)
{
    this->score = 0;

    this->text.setFont(assets.GetFont(Font::PixeloidSans));
    this->text.setCharacterSize(42);
    this->text.setString(GetString());
    this->text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
    this->text.setPosition(SCREEN_WIDTH - 240.f, SCREEN_HEIGHT / 16.f);
}

ScoreManager::ScoreManager(AssetManager& assets, Score::Type type, int score)
    : ScoreManager(assets, type)
{
    this->score = score;
}

void ScoreManager::LoadScoreFromFile()
{
    std::ifstream file("score.txt");
    std::string text;

    if (file.is_open())
    {
        std::getline(file, text);

        SetScore(text.size() == 0 ? 0 : std::stoi(text));

        file.close();
    }
}

void ScoreManager::SaveScoreInFile() const
{
    std::ifstream file("score.txt");
    std::string text;
    int saved_score = 0;

    if (file.is_open())
    {
        std::getline(file, text);
        if (!text.empty())
        {
            saved_score = std::stoi(text);
        }
        file.close();
    }

    if (this->score > saved_score)
    {
        std::ofstream outFile("score.txt", std::ios::trunc);
        if (outFile.is_open())
        {
            outFile << std::to_string(this->score);
            outFile.close();
        }
    }
}

void ScoreManager::SetScore(int new_score)
{
    this->score = new_score;
    this->text.setString(GetString());
    this->text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
}

void ScoreManager::SetPosition(sf::Vector2f pos)
{
    this->text.setPosition(pos);
}

void ScoreManager::AddToScore(int add_val)
{
    this->score += add_val;
    this->text.setString(GetString());
    this->text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
}

void ScoreManager::Draw(sf::RenderWindow& window)
{
    window.draw(this->text);
}
