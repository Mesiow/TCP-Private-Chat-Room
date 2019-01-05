#include "Client.h"

int Client::textYPosition = 1;
Client::Client(const std::string id, sf::IpAddress address, unsigned short serverPort)
{
	this->id = id;
	this->serverAddress = address;
	this->serverPort = serverPort; //port of the server

	font = ResourceManager::loadFont("Font/Rubik.ttf");
}

Client::~Client()
{
	
}


bool Client::connect()
{
	if (clientSocket.connect(serverAddress, serverPort) == sf::Socket::Done)
	{
		std::cout << "You connected" << std::endl;
	
		sf::Packet send;
		send << id;
		clientSocket.send(send);
		clientSocket.setBlocking(false);

		return true;
	}
	return false;
}

void Client::login()
{
	sf::Packet send;
	Packet pack = LOGIN;
	msg = "";
	send << id << msg << pack;
	clientSocket.send(send);
}

void Client::disconnect()
{
	sf::Packet send;
	Packet pack = DISCONNECT;
	msg = "";
	send << id << msg << pack;
	clientSocket.send(send); //send disconnection packet

	clientSocket.disconnect();
}

void Client::draw(sf::RenderTarget & target)
{
	target.draw(drawText);
	for(std::size_t i=0; i<texts.size(); i++)
		target.draw(texts[i]);
}

void Client::input(sf::Event &e)
{
	switch (e.type)
	{
	
	case sf::Event::KeyPressed:
	{
		if (e.key.code == sf::Keyboard::BackSpace)
		{
			if (msg.size() > 0) //only delete characters if message size is greater than zero
			{
				msg.erase(msg.begin() + msg.size() - 1, msg.end()); 
				drawText.setString(msg);
			}
		}
		else if (e.key.code == sf::Keyboard::Return)
		{
			textYPosition++;
			sf::Text text(msg, *font, 20);
			text.setFillColor(sf::Color::Red); //red indicates the msg has been sent
			
			Send(); //send message to server
			text.setPosition(10.0f, (float)textYPosition * 30.0f);

			texts.push_back(text);
			msg = " ";
			drawText.setString(msg);
		}
	}
		break;

		case sf::Event::TextEntered:
		{
			auto key = e.text.unicode;
			if (key == 8 || key == 13 || key ==27) //8 is backspace, 13 is enter, append characters to string unless its a backspace or enter
				break;
			
			msg += (char)key; //append to string
			sf::Text text(msg, *font, 20);
			text.setFillColor(sf::Color::Green);
			text.setPosition(15, 30);
			drawText = text;
		}
			break;
	}
}

void Client::Send()
{
	sf::Packet send;
	Packet pack = MESSAGE;
	send << id << msg << pack;
	clientSocket.send(send); //send id , msg and packet type to server
}

void Client::Receive()
{
	sf::Packet recv;
	std::string id;
	std::string message;
    std::uint32_t pack; //packet type

	if (clientSocket.receive(recv) != sf::Socket::Done)
		return;

	if (recv.getDataSize() > 0) //if bytes received are greater than zero
	{
		recv >> id >> message >> pack;
		auto packetType = (Packet)pack;

		textYPosition++;
		switch (packetType)
		{

		case LOGIN:
		{
			std::string mesg = id + " connected";
			sf::Text connectText(mesg, *font, 20);
			connectText.setFillColor(sf::Color::White);
			connectText.setPosition(0.0f, (float)textYPosition * 30.0f);
			texts.push_back(connectText);
		}
		break;

		case MESSAGE:
		{
			std::string remoteMsg = " " + id + ": " + message;
			sf::Text remoteText(remoteMsg, *font, 20);
			remoteText.setFillColor(sf::Color::Blue);
			remoteText.setPosition(0.0f, (float)textYPosition * 30.0f);
			texts.push_back(remoteText);
		}
			break;

		case DISCONNECT:
		{
			std::string mesg = id + " disconnected";
			sf::Text disconnectText(mesg, *font, 20);
			disconnectText.setFillColor(sf::Color::White);;
			disconnectText.setPosition(0.0f, (float)textYPosition * 30.0f);
			texts.push_back(disconnectText);
		}
		break;

		default:
			break;
		}
	}
}

