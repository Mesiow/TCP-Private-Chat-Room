#pragma once
#include "State.h"
#include "../Gui.h"
#include "../Client.h"

class Chat_State : public State
{
public:
	Chat_State(App &app, info &inputInfo);
	~Chat_State();

	void handleEvent(sf::Event &e)override;
	void handleInput()override;
	void update()override;
	void draw(sf::RenderTarget &target)override;

private:
	void initClient();
	void initUI();

private:
	std::vector<Gui::Box> boxes;
	std::vector<Gui::Button> buttons;
	std::vector<Gui::Text> texts;

private:
	info clientInfo;
	Client *client;
};
