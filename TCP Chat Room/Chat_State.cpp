#include "Chat_State.h"
#include "App.h"

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

}

void Chat_State::update()
{
	client->Receive();
}

void Chat_State::draw(sf::RenderTarget & target)
{
	for (auto &b : boxes)
		b.draw(target);

	client->draw(target);
}

void Chat_State::initClient()
{
	if (!client->connect())
		std::cout << "Client failed to connect" << std::endl;
}

void Chat_State::initUI()
{
	Gui::Box textBox(sf::Vector2f(380, 40), sf::Vector2f(750, 25), sf::Color::Transparent, true);
	boxes.emplace_back(textBox);

	Gui::Box windowBoundBox(sf::Vector2f(textBox.getPosition().x, textBox.getPosition().y + 270),
		sf::Vector2f(app->getWindow().getSize().x - 50, app->getWindow().getSize().y - 100),
		sf::Color::Transparent, true);
	boxes.emplace_back(windowBoundBox);
}
