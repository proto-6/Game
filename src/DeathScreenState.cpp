#include "DeathScreenState.h"

DeathScreenState::DeathScreenState(GameDataRef data, ScoreManager score)
	: data(data), score(score), button("Alright"), hover_button_type(ButtonName::None)
{

}

void DeathScreenState::Init()
{
	this->button.SetFont(Font::PixeloidSans, data);
	this->message.setFont(this->data->assets.GetFont(Font::PixeloidSans));
	this->message.setCharacterSize(42);
	int record = this->score.GetScore();
	if (record > 3000)
	{
		this->message.setString("Wow...");
	}
	else if (record > 2000)
	{
		this->message.setString("That's good");
	}
	else if (record > 800)
	{
		this->message.setString("That's alright, I guess...");
	}
	else if (record >= 0)
	{
		this->message.setString("Well, you tried :)");
	}
	this->message.setOrigin(this->message.getGlobalBounds().getSize() / 2.f + this->message.getLocalBounds().getPosition());
	this->message.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 50.f));

	this->score.SetPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 50.f));

	this->button.SetPosition(SCREEN_WIDTH / 2.f - this->button.GetGlobalBounds().getSize().x / 2.f, SCREEN_HEIGHT / 2.f + 150.f);

	hover_button_type = ButtonName::None;

	this->data->window.setView(this->data->window.getDefaultView());

	this->score.SaveScoreInFile();
}

void DeathScreenState::HandleInput(float dt)
{
	sf::Event ev;

	while (data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) this->data->window.close();
		else if (ev.type == sf::Event::MouseButtonReleased)
		{
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				if (hover_button_type == ButtonName::Alright)
				{
					data->stack.AddState(StatePtr(new MainMenuState(data)), true);

				}
				else if (hover_button_type == ButtonName::None)
				{
				}
			}
		}
	}
}

void DeathScreenState::Update(float dt)
{
	bool contains = button.GetGlobalBounds().contains(this->data->window.mapPixelToCoords(sf::Mouse::getPosition(this->data->window)));

	if (contains)
	{
		button.Hover(sf::Vector2f(button.GetOriginalSize().x + 5.f, button.GetOriginalSize().y + 5.f), sf::Mouse::getPosition(this->data->window), 0.01f);
		hover_button_type = button.GetButtonType();

	}
	else if (!contains)
	{
		button.Hover(button.GetOriginalSize(), sf::Mouse::getPosition(this->data->window), 0.01f);

		if (hover_button_type == button.GetButtonType())
		{
			hover_button_type = ButtonName::Type::None;
		}


	}
}

void DeathScreenState::Render(float dt)
{
	this->data->window.clear(sf::Color(16, 16, 16));

	this->data->window.draw(this->message);
	this->data->window.draw(this->button);
	this->score.Draw(this->data->window);

	data->window.display();
}

