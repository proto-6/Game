#include "Application.h"


#include "SplashState.h"

Application::Application(int width, int heigh, std::string title)
{
	data = std::make_shared<GameData>();
	data->window.create(sf::VideoMode(width, heigh), title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize | sf::Style::Fullscreen);
	data->stack.AddState(StatePtr(new SplashState(this->data)), false);
}

void Application::Run()
{
	float new_time, frame_time, interpolation;

	float current_time = this->clock.getElapsedTime().asSeconds();
	float accumulator = 0.f;
	
	while (this->data->window.isOpen())
	{
		this->data->stack.ProcessStateChanges();

		new_time = this->clock.getElapsedTime().asSeconds();
		frame_time = new_time - current_time;

		

		current_time = new_time;
		accumulator += frame_time;

		while (accumulator >= dt)
		{
			this->data->stack.GetActiveState()->HandleInput(dt);
			this->data->stack.GetActiveState()->Update(dt);
			
			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->data->stack.GetActiveState()->Render(interpolation);
	}

}
