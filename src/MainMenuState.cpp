#include "MainMenuState.h"

#include <iostream>



MainMenuState::MainMenuState(GameDataRef data) 
	: _data(data), _hover_button_type(ButtonName::None)
{
	
	
}

void MainMenuState::MoveCharacter(sf::Vector2f pos2, float dt)
{
	/*SetSize(original_size + speed * (hover_size - original_size));*/
	sf::Vector2f new_pos = hero->GetPosition() + (dt / 100.f) * (pos2 - hero->GetPosition());
	hero->SetPosition(new_pos);
}

void MainMenuState::Init()
{
	InitButtons();
	InitCharacter();
	
	_hover_button_type = ButtonName::None;

}

void MainMenuState::InitButtons()
{
	std::vector<sf::String> button_names = { "Play", "Settings", "Exit" };
	for (auto& button_name : button_names)
	{
		if (this->_buttons.empty())
		{
			this->_buttons.push_back(std::move(button_name));
			this->_buttons.back().SetFont(Font::PixeloidSans, _data);

			this->_buttons.back().SetPosition
			(
				this->_data->window.getSize().x / 8.f - this->_buttons.back().GetSize().x / 8.f,
				this->_data->window.getSize().y / 1.8f
			);
		}
		else
		{
			float x = this->_data->window.getSize().x / 8.f - this->_buttons.back().GetSize().x / 8.f;
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
}

void MainMenuState::InitCharacter()
{
	hero = std::make_shared<Character>(Character(this->_data->assets));
	
}




void MainMenuState::HandleInput()
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
					_data->stack.AddState(StatePtr(new GameMenuState(_data)), true);
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

void MainMenuState::Update(float dt)
{
	UpdateButtons();
	
	/* Cool animation, saving for later (maybe implement so character goes out of bound to the right side, 
	after that returns to designed for him place)
	MoveCharacter(
		sf::Vector2f
		(
			this->_data->window.getSize().x / (2/3.f),
			this->_data->window.getSize().y / 3.f
		), 
		dt);*/
	MoveCharacter(sf::Vector2f(1220, 360), dt);
	hero->Update(dt);
	
	
}

void MainMenuState::UpdateButtons()
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

void MainMenuState::Render(float dt)
{
	this->_data->window.clear(sf::Color(16,16,16));

	hero->Draw(&this->_data->window, dt);
	for (auto& button : this->_buttons)
	{
		this->_data->window.draw(button);
		
	}
	

	_data->window.display();
}
