#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

namespace Gui
{
	class Box //entity that the user cannot interact with
	{
	public:
		Box(sf::Vector2f position, sf::Vector2f size, sf::Color color, bool transparent=false);
		~Box();

	public:
		void update();
		void draw(sf::RenderTarget &target);

	public:
		void setPosition(sf::Vector2f position) { box.setPosition(position); }
		void setOrigin(sf::Vector2f origin) { box.setOrigin(origin); }

	public:
		sf::Vector2f getPosition()const { return box.getPosition(); }
		sf::Vector2f getSize()const { return box.getSize(); }

	private:
		sf::RectangleShape box;
		sf::Vector2f pos;
	};


	class Button //interactive entity that does something upon clicking
	{
	public:
		enum class State
		{
			CLICKED = 0,
			HOVERING,
			NONE,
		};
		Button() = default;
		Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, const std::string buttonID, bool transparent=false);
		~Button();

	public:
		void update(sf::RenderWindow &window);
		void draw(sf::RenderTarget &target);

	public:
		void setPosition(sf::Vector2f pos) { button.setPosition(pos); }
		void setOrigin(sf::Vector2f origin) { button.setOrigin(origin); }
		void setID(const std::string id) { buttonID = id; }

	public:
		sf::FloatRect getBounds()const { return button.getGlobalBounds(); }
		sf::Vector2f getPosition()const { return button.getPosition(); }
		sf::Vector2f getOrigin()const { return button.getOrigin(); }

	private:
		void checkClicked(sf::RenderWindow &window);
		void checkMouseHovering(sf::RenderWindow &window);

	public:
		State getButtonState()const { return buttonState; }
		std::string getButtonID()const { return buttonID; }

	private:
		sf::RectangleShape button;
		sf::Vector2f pos;
		sf::Vector2f size;

	private:
		std::string buttonID;
		State buttonState;
		bool transparent;
	};

	class Text
	{
	public:
		Text(sf::Vector2f position, sf::Color color, sf::Font &font, std::string text, unsigned int characterSize);
		~Text();

	public:
		void update();
		void draw(sf::RenderTarget &target);

	public:
		void setString(const std::string &s) { text.setString(s); }
		void setFont(sf::Font &font) { text.setFont(font); }

	public:
		sf::Vector2f getPosition()const { return text.getPosition(); }

	private:
		sf::Text text;
		sf::Vector2f pos;
		sf::Vector2f size;

	private:
		std::string txt;
		unsigned int charSize;

	};
};