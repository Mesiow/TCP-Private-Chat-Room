#pragma once
#include <iostream>
#include <SFML/Network.hpp>
#include <vector>
#include <unordered_map>
#include "Utils/Utils.h"

class Server
{
public:
	Server(unsigned short port);
	~Server();

public:
	void init();
	void launch();

private:
	void Accept();
	void Send();

private:
	void updateUserCount();
	
private:
	sf::SocketSelector selector; //selector to handle multiple clients
	sf::TcpListener listener;
	std::vector<sf::TcpSocket*> clients;
	std::unordered_map<unsigned short, sf::IpAddress> clientID;

private:
	unsigned short port;
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	bool running = true;
	int clientCount;
};