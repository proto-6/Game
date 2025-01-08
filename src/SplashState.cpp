#include "SplashState.h"
#include "MainMenuState.h"

#include <sstream>
#include <cassert>

SplashState::SplashState(GameDataRef data) : _data(data)
{
	
}

void SplashState::Init()
{
	_data->assets.LoadFont(Font::Type::PixeloidSans, "../resource/fonts/PixeloidSans.ttf");
	_data->assets.LoadTexture(Texture::Type::Blue_Flame, "../resource/assets/blue-flame.png");

	_logo.setTexture(_data->assets.GetTexture(Texture::Type::Blue_Flame));
	_logo.setScale(0.8f, 0.8f);
	_logo.setPosition
	(
		this->_data->window.getSize().x/2 - _logo.getGlobalBounds().width / 2,
		this->_data->window.getSize().y/2 - _logo.getGlobalBounds().height / 1.3f
	);
	
	_text.setFont(_data->assets.GetFont(Font::Type::PixeloidSans));
	_text.setString("Magic Tinkerer");
	_text.setCharacterSize(72);
	_text.setFillColor(sf::Color::White);
	_text.setOrigin(_text.getGlobalBounds().getSize() / 2.f);
	_text.setPosition
	(
		this->_data->window.getSize().x / 2.f,
			(this->_data->window.getSize().y / 2.f)  + this->_text.getGlobalBounds().height * 2.f
	); // Pure magic
}

void SplashState::HandleInput(float dt)
{
	sf::Event ev;

	while (_data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			_data->window.close();
			
		}
	}
}

void SplashState::Update(float dt)
{
	if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		_data->stack.AddState(StatePtr(new MainMenuState(_data)), true);
	} 
}

void SplashState::Render(float dt)
{
	_data->window.clear();
	
	_data->window.draw(_logo);
	_data->window.draw(_text);

	_data->window.display();
}
