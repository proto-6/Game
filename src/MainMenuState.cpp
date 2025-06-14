#include "MainMenuState.h"



MainMenuState::MainMenuState(GameDataRef data) 
	: data(data), hover_button_type(ButtonName::None), hi_score(data->assets, Score::Type::Hi_Score)
{
	
	
}

void MainMenuState::MoveCharacter(sf::Vector2f pos2, float dt)
{
	sf::Vector2f move_val = (dt) * (pos2 - hero->GetPosition());
	hero->Move(move_val.x < 0.2f ? 0 : move_val.x, move_val.y < 0.2f ? 0 : move_val.y); // So character doesn't move infinetly
	
	
	
}

void MainMenuState::Init()
{
	InitButtons();
	InitCharacter();

	
	hover_button_type = ButtonName::None;

}

void MainMenuState::InitButtons()
{
	std::vector<sf::String> button_names = { "Play", "Exit" };
	for (auto& button_name : button_names)
	{
		if (this->buttons.empty())
		{
			this->buttons.push_back(std::move(button_name));
			this->buttons.back().SetFont(Font::PixeloidSans, data);

			/*this->buttons.back().SetPosition
			(
				this->data->window.getSize().x / 8.f - this->buttons.back().GetSize().x / 8.f,
				this->data->window.getSize().y / 1.4f
			);*/
			this->buttons.back().SetPosition
			(
				(this->data->window.getSize().x / 100.f) * 7.f,
				(this->data->window.getSize().y / 100.f) * 72.f
			);
		}
		else
		{
			float x = this->data->window.getSize().x / 100.f * 7.f;
			float y = this->buttons.back().GetPosition().y + this->buttons.back().GetSize().y;
			float gap = ((20.f) * SCREEN_HEIGHT) / 1080.f;


			this->buttons.push_back(std::move(button_name));
			this->buttons.back().SetFont(Font::PixeloidSans, data);

			this->buttons.back().SetPosition
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
	hero = std::make_shared<Character>(Character(this->data->assets));
	hero->SetScale(24, 24);
	hero->SetState(CharacterMovement::State::Pose);
	
	hero->SetOrigin(hero->GetLocalBounds().width / 2.f, hero->GetLocalBounds().height / 2.f);
}




void MainMenuState::HandleInput(float dt)
{
	sf::Event ev;

	while (data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) this->data->window.close();
		else if (ev.type == sf::Event::MouseButtonReleased)
		{
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				if (hover_button_type == ButtonName::Play)
				{
					// Changed from GameMenuState to BattleState (in debugging purposes)
					data->stack.AddState(StatePtr(new BattleState(data, hero)), true);
					
				}
				else if (hover_button_type == ButtonName::Exit)
				{
					this->data->window.close();
				}
				else if (hover_button_type == ButtonName::None)
				{
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
			this->data->window.getSize().x / (2/3.f),
			this->data->window.getSize().y / 3.f
		), 
		dt);*/
	MoveCharacter(sf::Vector2f(SCREEN_WIDTH * 2 / 3.f, SCREEN_HEIGHT / 1.5f), dt);
	hero->UpdateAnimation(dt);
	
	
}

void MainMenuState::UpdateButtons()
{
	for (auto& button : this->buttons)
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
}

void MainMenuState::Render(float dt)
{
	this->data->window.clear(sf::Color(16,16,16));

	hero->Draw(&this->data->window, dt);
	for (auto& button : this->buttons)
	{
		this->data->window.draw(button);
		
	}

	this->hi_score.Draw(this->data->window);


	data->window.display();
}
