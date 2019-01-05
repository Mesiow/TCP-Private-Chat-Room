#include "Chat_State.h"
#include "App.h"
#include "Login_State.h"

Chat_State::Chat_State(App &app, info &inputInfo)
	:State(app)
{
	clientInfo.ipaddress = inputInfo.ipaddress;
	clientInfo.port = inputInfo.port;
	clientInfo.name = inputInfo.name;

	client = new Client(clientInfo.name, clientInfo.ipaddress, clientInfo.port);
	initUI();
	initClient();
}

Chat_State::~Chat_State()
{
	delete client;
}

void Chat_State::handleEvent(sf::Event & e)
{
	client->input(e);
}

void Chat_State::handleInput()
{
	for (std::size_t i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].getButtonState() == Gui::Button::State::CLICKED)
		{
			if (buttons[i].getButtonID() == "Disconnect")
			{
				app->pop_state();
				//app->pushState(std::make_unique<Login_State>(*app)); //pop the current chat state and go back to login state
			}
		}
	}
}

void Chat_State::update()
{
	client->Receive();

	for (auto &b : buttons)
		b.update(App::getWindow());
}

void Chat_State::draw(sf::RenderTarget & target)
{
	for (auto &b : boxes)
		b.draw(target);

	for (auto &b : buttons)
		b.draw(target);

	for (auto &t : texts)
		t.draw(target);

	client->draw(target);
}

void Chat_State::initClient()
{
	if (!client->connect())
		std::cout << "Client failed to connect" << std::endl;
}

void Chat_State::initUI()
{
	sf::Font *font = ResourceManager::loadFont("Font/Rubik.ttf");

	Gui::Box textBox(sf::Vector2f(380, 40), sf::Vector2f(750, 25), sf::Color::Transparent, true);
	boxes.emplace_back(textBox);

	Gui::Box windowBoundBox(sf::Vector2f(textBox.getPosition().x, textBox.getPosition().y + 270),
		sf::Vector2f(app->getWindow().getSize().x - 50, app->getWindow().getSize().y - 100),
		sf::Color::Transparent, true);
	boxes.emplace_back(windowBoundBox);

	Gui::Button disconnectButton(sf::Vector2f(WIDTH - 90, HEIGHT - 15),
		sf::Vector2f(90, 20), sf::Color::Transparent, std::string("Disconnect"), true);
	buttons.emplace_back(disconnectButton);

	Gui::Text disconnectText(sf::Vector2f(WIDTH - 130, HEIGHT - 25), sf::Color::White, *font, "Disconnect", 15);
	texts.emplace_back(disconnectText);
}
