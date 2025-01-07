#include "Application.h"


#include "SplashState.h"

Application::Application(int width, int heigh, std::string title)
{
	_data = std::make_shared<GameData>();
	_data->window.create(sf::VideoMode(width, heigh), title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize | sf::Style::Fullscreen);
	_data->stack.AddState(StatePtr(new SplashState(this->_data)), false);
}

void Application::Run()
{
	float new_time, frame_time, interpolation;

	float current_time = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.f;
	
	while (this->_data->window.isOpen())
	{
		this->_data->stack.ProcessStateChanges();

		new_time = this->_clock.getElapsedTime().asSeconds();
		frame_time = new_time - current_time;

		if (frame_time < 0.25f)
		{
			frame_time = 0.25f;
		}

		current_time = new_time;
		accumulator += frame_time;

		while (accumulator >= dt)
		{
			this->_data->stack.GetActiveState()->HandleInput();
			this->_data->stack.GetActiveState()->Update(dt);
			
			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->_data->stack.GetActiveState()->Render(interpolation);
	}

}
