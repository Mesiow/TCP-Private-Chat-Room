#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "../Gui.h"

class App;

class Login_State : public State
{
public:
	Login_State(App &app);
	~Login_State();

	void handleEvent(sf::Event &e)override;
	void handleInput()override;
	void update()override;
	void draw(sf::RenderTarget &target)override;

public:
	void initGUI();
	void clearData();


private:
	std::vector<Gui::Box> boxes;
	std::vector<Gui::Button> buttons;
	std::vector<Gui::Text> texts;
	std::vector<sf::Text> sfTexts;
	sf::Text currentText;
	sf::Font *font;

private:
	info clientInfo;
	std::string text;
	Gui::Button *buttonClicked;
};