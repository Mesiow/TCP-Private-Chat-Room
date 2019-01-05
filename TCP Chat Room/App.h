#pragma once
#include <SFML/Graphics.hpp>
#include "Server.h"
#include "Client.h"
#include "Gui.h"
#include "State.h"
#include "ResourceManager.h"
#include <unordered_map>
#include <memory>
#include <stack>

#define WIDTH 800
#define HEIGHT 600

class App : public sf::NonCopyable
{
public:
	App();
	~App();

public:
	void run();
	void init(const char option, unsigned short serverPort);

private:
	void update();
	void draw();
	void display();
	void clear();
	void pollEvents(sf::Event &e);

public:
	template<typename T, typename... Args>
	inline void pushState(Args&&... args);

	void pushState(std::unique_ptr<State> newState);
	void pop_state();

public:
	State &getCurrentState() { return *states.top(); }
	static sf::RenderWindow &getWindow() { return *window; }

private:
	static sf::RenderWindow *window;
	Server *server;
	Client *client;

private:
	std::stack<std::unique_ptr<State>> states;

private:
	char host;
};

template<typename T, typename... Args>
inline void App::pushState(Args&&... args)
{
	pushState(std::make_unique<T>(std::forward<Args>(args)...)); // push new state into stack container
}