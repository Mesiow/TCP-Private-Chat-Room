#pragma once
#include <SFML/Graphics.hpp>

class App;

struct info
{
	std::string ipaddress;
	unsigned short port;
	std::string name;
};


class State : public sf::NonCopyable
{
public:
	State(App &app)
		:app(&app) {}

	virtual ~State() = default;

	virtual void handleEvent(sf::Event &e) = 0;
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderTarget &target) = 0;

protected:
	App *app;
};