#include "GameMenuState.h"

#include <iostream>

GameMenuState::GameMenuState(GameDataRef data)
	: _data(data), _hover_button_type(ButtonName::Type::None)
{

}

void GameMenuState::Init()
{
	this->_hover_button_type = ButtonName::Type::None;
	this->_data->assets.LoadTexture(Texture::GameMenu_Background, "../resource/assets/backgrounds/Dungeon background cartoon 2d 6.jpg");

	this->_background.setTexture(this->_data->assets.GetTexture(Texture::GameMenu_Background));
	this->_background.setOrigin(this->_background.getGlobalBounds().getSize() / 2.f);
	this->_background.setPosition(this->_data->window.getSize().x / 2.f, this->_data->window.getSize().y / 2.f);
	this->_background.setScale(this->_data->window.getSize().x / 1536.f, this->_data->window.getSize().y / 1536.f); // 1536 is resolution of background picture (yes, it's 1536x1536)

	std::vector<sf::String> button_names = { "Play", "Settings", "Exit" };
	for (auto& button_name : button_names)
	{
		if (this->_buttons.empty())
		{
			this->_buttons.push_back(std::move(button_name));
			this->_buttons.back().SetFont(Font::PixeloidSans, _data);

			this->_buttons.back().SetPosition
			(
				this->_data->window.getSize().x / 2.f - this->_buttons.back().GetSize().x / 2.f,
				this->_data->window.getSize().y / 2.5f
			);
		}
		else
		{
			float x = this->_data->window.getSize().x / 2.f - this->_buttons.back().GetSize().x / 2.f;
			float y = this->_buttons.back().GetPosition().y + this->_buttons.back().GetSize().y;
			float gap = this->_buttons.back().GetSize().y / 4.5f;

			this->_buttons.push_back(std::move(button_name));
			this->_buttons.back().SetFont(Font::PixeloidSans, _data);

			this->_buttons.back().SetPosition
			(
				x,
				y
				+ // add gap between buttons that depends on size of a button
				gap
			);
		}

	}

	_hover_button_type = ButtonName::None;

}

void GameMenuState::HandleInput(float dt)
{
	sf::Event ev;

	while (_data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) this->_data->window.close();
		else if (ev.type == sf::Event::MouseButtonReleased)
		{
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				if (_hover_button_type == ButtonName::Play)
				{
					std::cout << "Play Button pressed" << std::endl;
				}
				else if (_hover_button_type == ButtonName::Settings)
				{
					std::cout << "Setting Button presssed" << std::endl;
				}
				else if (_hover_button_type == ButtonName::Exit)
				{
					std::cout << "Exit Button pressed" << std::endl;
					this->_data->window.close();
				}
				else if (_hover_button_type == ButtonName::None)
				{
					std::cout << "Welp" << std::endl;
				}
			}
		}


	}
}

void GameMenuState::Update(float dt)
{
	for (auto& button : this->_buttons)
	{
		bool contains = button.GetGlobalBounds().contains(this->_data->window.mapPixelToCoords(sf::Mouse::getPosition(this->_data->window)));

		if (contains)
		{
			button.Hover(sf::Vector2f(305, 105), sf::Mouse::getPosition(this->_data->window), 0.01f);
			_hover_button_type = button.GetButtonType();

		}
		else if (!contains)
		{
			button.Hover(sf::Vector2f(300, 100), sf::Mouse::getPosition(this->_data->window), 0.01f);

			if (_hover_button_type == button.GetButtonType())
			{
				_hover_button_type = ButtonName::Type::None;
			}


		}
	}
}

void GameMenuState::Render(float dt)
{
	_data->window.clear();

	this->_data->window.draw(_background);

	for (auto& button : this->_buttons)
	{
		this->_data->window.draw(button);

	}


	_data->window.display();
}
