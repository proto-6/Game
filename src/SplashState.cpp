#include "SplashState.h"
#include "MainMenuState.h"

#include <sstream>
#include <cassert>

SplashState::SplashState(GameDataRef data) : data(data)
{
	
}

void SplashState::Init()
{
	data->assets.LoadFont(Font::Type::PixeloidSans, "../resource/fonts/PixeloidSans.ttf");
	data->assets.LoadTexture(Texture::Type::Blue_Flame, "../resource/assets/blue-flame.png");

	_logo.setTexture(data->assets.GetTexture(Texture::Type::Blue_Flame));
	_logo.setScale(0.8f, 0.8f);
	_logo.setPosition
	(
		this->data->window.getSize().x/2 - _logo.getGlobalBounds().width / 2,
		this->data->window.getSize().y/2 - _logo.getGlobalBounds().height / 1.3f
	);
	
	text.setFont(data->assets.GetFont(Font::Type::PixeloidSans));
	text.setString("Magic Tinkerer");
	text.setCharacterSize(72);
	text.setFillColor(sf::Color::White);
	text.setOrigin(text.getGlobalBounds().getSize() / 2.f);
	text.setPosition
	(
		this->data->window.getSize().x / 2.f,
			(this->data->window.getSize().y / 2.f)  + this->text.getGlobalBounds().height * 2.f
	); // Pure magic
}

void SplashState::HandleInput(float dt)
{
	sf::Event ev;

	while (data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			data->window.close();
			
		}
	}
}

void SplashState::Update(float dt)
{
	if (_clock.getElapsedTime().asSeconds() > SPLASHstate_SHOW_TIME)
	{
		data->stack.AddState(StatePtr(new MainMenuState(data)), true);
	} 
}

void SplashState::Render(float dt)
{
	data->window.clear();
	
	data->window.draw(_logo);
	data->window.draw(text);

	data->window.display();
}
