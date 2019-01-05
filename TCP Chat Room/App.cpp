#include "App.h"
#include "Login_State.h"

//TODO: continue abstracting data into the state classes

sf::RenderWindow *App::window;

App::App()
{
	
}

App::~App()
{
	if(window!=nullptr) //delete window if it was created
		delete window;
}

void App::run()
{
	while (window->isOpen() && !states.empty())
	{
		auto &state = getCurrentState(); //get reference to current state
		
		sf::Event e;
		pollEvents(e);
		state.handleInput();

		clear();
	
		state.update();
		state.draw(*window);

		display();
	}
}

void App::init(const char option, const unsigned short serverPort)
{
	this->host = option;

	if (host == 'S')
	{
		server = new Server(serverPort);
		server->init();
		server->launch();
		window = nullptr;
	}
	else if (host == 'C')
	{
		window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Chat", sf::Style::Default);
		pushState<Login_State>(*this); //begin application with login screen
	}
}

void App::update()
{

}

void App::draw()
{
	
}

void App::display()
{
	window->display();
}

void App::clear()
{
	window->clear(sf::Color(0, 0, 50, 200));
}

void App::pollEvents(sf::Event & e)
{
	while (window->pollEvent(e))
	{
		getCurrentState().handleEvent(e); //handle event in current state
		switch (e.type)
		{
		case sf::Event::Closed:
			window->close();	
		}
	}
}

void App::pushState(std::unique_ptr<State> newState)
{
	states.push(std::move(newState));
}

void App::pop_state()
{
	states.pop();
}
