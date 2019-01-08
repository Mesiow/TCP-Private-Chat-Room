#include "Server.h"

Server::Server(unsigned short port)
	:clientCount(0)
{
	this->port = port;
}

Server::~Server()
{

}

void Server::init()
{
	listener.listen(port, ip); //listen to connections on specified port and ip
	selector.add(listener); //add tcp listener to the selector
}

void Server::launch()
{
	std::cout << "Server Online" << std::endl;
	while (running)
	{
		if (selector.wait())
		{
			if (selector.isReady(listener)) //if listener is ready to receive data
			{
				Accept();
			}
			else
			{
				Send();
			}
		}
	}
}

void Server::Accept()
{
	sf::TcpSocket *socket = new sf::TcpSocket; //create socket for server to receive data
	listener.accept(*socket); //accept new socket

	sf::Packet packet;
	std::string id;

	if (socket->receive(packet) == sf::Socket::Done)
	{
		packet >> id; //put packet contents into id
		clientID[socket->getRemotePort()] = socket->getRemoteAddress();
		clientCount++;
	}

	std::cout << id << " has connected to the chat" << std::endl;
	clients.push_back(socket);
	selector.add(*socket);
}

void Server::Send()
{
	for (std::size_t i = 0; i < clients.size(); i++)
	{
		if (selector.isReady(*clients[i])) //if we are ready to receive connections for any of the clients
		{
			sf::Packet packet;
			sf::Packet send;
			
			//if one of the clients receives a packet
			if (clients[i]->receive(packet) == sf::Socket::Done)
			{
				std::string id;
				std::string msg;
				std::uint32_t pack; //packet type
				

				packet >> id >> msg >> pack; //write contents into id, msg and packet type
				send << id << msg << (Packet)pack; //put that data into a send packet

				for (std::size_t j = 0; j < clients.size(); j++)
				{
					if (i != j) //send to every other client but the one that sent it
					{
						clients[j]->send(send); //send id and message to clients
					}
				}
			}
		}
	}
}
