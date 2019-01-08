#include "Login_State.h"
#include "Chat_State.h"
#include "../App.h"

Login_State::Login_State(App & app)
	:State(app)
{
	initGUI();
}

Login_State::~Login_State()
{

}

void Login_State::handleEvent(sf::Event & e)
{
	switch (e.type)
	{
	case sf::Event::KeyPressed:
	{
		if (e.key.code == sf::Keyboard::BackSpace)
		{
			if (text.size() > 0) //only delete characters if message size is greater than zero
			{
				text.erase(text.begin() + text.size() - 1, text.end()); //delete last letter in string
				currentText.setString(text);
			}
		}
		else if (e.key.code == sf::Keyboard::Return ||
			     e.key.code==sf::Keyboard::Tab)
		{

			if (buttonClicked->getButtonID() == "IPInput")
				clientInfo.ipaddress = currentText.getString();
			else if (buttonClicked->getButtonID() == "PortInput")
			{
				std::string portString = currentText.getString(); //getString returns an sf::String, setting it to a standard string implicitly converts it
				clientInfo.port = std::stoi(portString); //std::stoi, string to int conversion
			}
			else if (buttonClicked->getButtonID() == "NameInput")
				clientInfo.name = currentText.getString();

			sfTexts.emplace_back(currentText);
			text.clear();
			currentText.setString(text);
		}
	}
	break;

	case sf::Event::TextEntered:
	{
		auto key = e.key.code;
		if (key == 8 || key == 13 || key == 27)
			break;

		if (buttonClicked)
		{
			text += (char)key;
			if (buttonClicked->getButtonID() == "IPInput")
			{
				auto pos = buttonClicked->getPosition();

				sf::Text input(text, *font, 15);
				input.setPosition(sf::Vector2f(pos.x - 70, pos.y - 10));
				currentText = input;
			}
			else if (buttonClicked->getButtonID() == "PortInput")
			{
				auto pos = buttonClicked->getPosition();

				sf::Text input(text, *font, 15);
				input.setPosition(sf::Vector2f(pos.x - 70, pos.y - 10));
				currentText = input;
			}
			else if (buttonClicked->getButtonID() == "NameInput")
			{
				auto pos = buttonClicked->getPosition();

				sf::Text input(text, *font, 15);
				input.setPosition(sf::Vector2f(pos.x - 70, pos.y - 10));
				currentText = input;
			}
		}
	}
	break;
	}
}

void Login_State::handleInput()
{
	for (std::size_t i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].getButtonState() == Gui::Button::State::CLICKED)
		{
			buttonClicked = &buttons[i];
			if (buttons[i].getButtonID() == "Connect")
			{
				app->pushState(std::make_unique<Chat_State>(*app, clientInfo)); //change state to chat state
				clearData();
			}
		}
	}
}

void Login_State::update()
{
	for (auto &b : buttons)
		b.update(App::getWindow());
}

void Login_State::draw(sf::RenderTarget & target)
{
	for (auto &box : boxes)
		box.draw(target);

	for (auto &b : buttons)
		b.draw(target);

	for (auto &t : texts)
		t.draw(target);

	for (auto &t : sfTexts)
		target.draw(t);

	target.draw(currentText);

}

void Login_State::initGUI()
{
	//gui for login state
	font = ResourceManager::loadFont("Font/Rubik.ttf");
	currentText.setFont(*font);
	currentText.setCharacterSize(15);
	currentText.setFillColor(sf::Color::White);


	Gui::Box loginBox(sf::Vector2f(App::getWindow().getSize().x / 2, App::getWindow().getSize().y / 2), //box
		sf::Vector2f(200, 400), sf::Color(150, 150, 150, 255));
	boxes.emplace_back(loginBox);

	Gui::Button connectButton(sf::Vector2f(loginBox.getPosition().x, loginBox.getPosition().y + loginBox.getSize().y / 2 - 20), //button
		sf::Vector2f(70, 20), sf::Color::Transparent, std::string("Connect"), true);
	buttons.emplace_back(connectButton);

	Gui::Text connectText(sf::Vector2f(connectButton.getPosition().x - 30, connectButton.getPosition().y - 10), //text
		sf::Color::White, *font, std::string("Connect"), 15); //text
	texts.emplace_back(connectText);

	Gui::Text enterIP(sf::Vector2f(App::getWindow().getSize().x / 2 - 40, App::getWindow().getSize().y / 2 - 130), //text
		sf::Color::Black, *font, "Enter IP: ", 15);
	texts.emplace_back(enterIP);

	Gui::Text enterPort(sf::Vector2f(enterIP.getPosition().x, enterIP.getPosition().y + 70), //text
		sf::Color::White, *font, std::string("Enter port: "), 15);
	texts.emplace_back(enterPort);

	Gui::Text enterID(sf::Vector2f(enterPort.getPosition().x, enterPort.getPosition().y + 70), //text
		sf::Color::White, *font, std::string("Enter Name: "), 15);
	texts.emplace_back(enterID);

	Gui::Button inputButton(sf::Vector2f(enterIP.getPosition().x + 40, enterIP.getPosition().y + 40),
		sf::Vector2f(150, 20), sf::Color::Transparent, std::string("IPInput"), true);
	buttons.emplace_back(inputButton);

	Gui::Button button2 = inputButton;
	button2.setPosition(sf::Vector2f(inputButton.getPosition().x, inputButton.getPosition().y + 70));
	button2.setID(std::string("PortInput"));
	buttons.emplace_back(button2);

	Gui::Button button3 = button2;
	button3.setPosition(sf::Vector2f(button2.getPosition().x, button2.getPosition().y + 70));
	button3.setID(std::string("NameInput"));
	buttons.emplace_back(button3);
}

void Login_State::clearData()
{
	//free data we don't need in the chat state
	sfTexts.clear();
	clientInfo.clear();
}





