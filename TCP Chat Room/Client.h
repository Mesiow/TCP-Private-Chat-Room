#pragma once
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Utils/Utils.h"
#include "Utils/ResourceManager.h"

class Client
{
public:
	Client(const std::string &id, sf::IpAddress address, unsigned short remotePort);
	~Client();

public:
	bool connect();
	void login();
	void disconnect();
	void Receive();

private:
	void Send();

public:
	void draw(sf::RenderTarget &target);
	void input(sf::Event &e);

private:
	std::string id;
	sf::TcpSocket clientSocket;
	sf::IpAddress serverAddress;
	unsigned short serverPort;

private:
	sf::Font *font;
	std::vector<sf::Text> texts; //sent texts to store and draw
	sf::Text drawText; //typing text to draw currently
	std::string msg;
	
private:
	static int textYPosition;
};