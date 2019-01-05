#pragma once
#include <SFML/Graphics.hpp>
#include "Server.h"
#include "Client.h"
#include "Gui.h"
#include "States/State.h"
#include "Utils/ResourceManager.h"
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
	void pop();

public:
	State &getCurrentState() { return *states.back(); }
	static sf::RenderWindow &getWindow() { return *window; }

private:
	void pop_state();

private:
	static sf::RenderWindow *window;
	Server *server;
	Client *client;

private:
	std::vector<std::unique_ptr<State>> states;
	std::unique_ptr<State> change;

private:
	char host;
	bool popState = false;
	bool changeState = false;
	bool exit = false;
};

template<typename T, typename... Args>
inline void App::pushState(Args&&... args)
{
	pushState(std::make_unique<T>(std::forward<Args>(args)...)); // push new state into vector
}