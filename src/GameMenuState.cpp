#include "GameMenuState.h"


GameMenuState::GameMenuState(GameDataRef data)
	: data(data), _hover_button_type(ButtonName::Type::None)
{

}

void GameMenuState::Init()
{
	this->_hover_button_type = ButtonName::Type::None;
	this->data->assets.LoadTexture(Texture::GameMenu_Background, "../resource/assets/backgrounds/Dungeon background cartoon 2d 6.jpg");

	this->_background.setTexture(this->data->assets.GetTexture(Texture::GameMenu_Background));
	this->_background.setOrigin(this->_background.getGlobalBounds().getSize() / 2.f);
	this->_background.setPosition(this->data->window.getSize().x / 2.f, this->data->window.getSize().y / 2.f);
	this->_background.setScale(this->data->window.getSize().x / 1536.f, this->data->window.getSize().y / 1536.f); // 1536 is resolution of background picture (yes, it's 1536x1536)

	std::vector<sf::String> button_names = { "Play", "Settings", "Exit" };
	for (auto& button_name : button_names)
	{
		if (this->_buttons.empty())
		{
			this->_buttons.push_back(std::move(button_name));
			this->_buttons.back().SetFont(Font::PixeloidSans, data);

			this->_buttons.back().SetPosition
			(
				this->data->window.getSize().x / 2.f - this->_buttons.back().GetSize().x / 2.f,
				this->data->window.getSize().y / 2.5f
			);
		}
		else
		{
			float x = this->data->window.getSize().x / 2.f - this->_buttons.back().GetSize().x / 2.f;
			float y = this->_buttons.back().GetPosition().y + this->_buttons.back().GetSize().y;
			float gap = this->_buttons.back().GetSize().y / 4.5f;

			this->_buttons.push_back(std::move(button_name));
			this->_buttons.back().SetFont(Font::PixeloidSans, data);

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

	while (data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) this->data->window.close();
		else if (ev.type == sf::Event::MouseButtonReleased)
		{
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				if (_hover_button_type == ButtonName::Play)
				{
				}
				else if (_hover_button_type == ButtonName::Settings)
				{
				}
				else if (_hover_button_type == ButtonName::Exit)
				{
					this->data->window.close();
				}
				else if (_hover_button_type == ButtonName::None)
				{
				}
			}
		}


	}
}

void GameMenuState::Update(float dt)
{
	for (auto& button : this->_buttons)
	{
		bool contains = button.GetGlobalBounds().contains(this->data->window.mapPixelToCoords(sf::Mouse::getPosition(this->data->window)));

		if (contains)
		{
			button.Hover(sf::Vector2f(305, 105), sf::Mouse::getPosition(this->data->window), 0.01f);
			_hover_button_type = button.GetButtonType();

		}
		else if (!contains)
		{
			button.Hover(sf::Vector2f(300, 100), sf::Mouse::getPosition(this->data->window), 0.01f);

			if (_hover_button_type == button.GetButtonType())
			{
				_hover_button_type = ButtonName::Type::None;
			}


		}
	}
}

void GameMenuState::Render(float dt)
{
	data->window.clear();

	this->data->window.draw(_background);

	for (auto& button : this->_buttons)
	{
		this->data->window.draw(button);

	}


	data->window.display();
}
