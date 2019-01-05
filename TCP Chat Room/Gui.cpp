#include "Gui.h"

namespace Gui
{
	//start
	Box::Box(sf::Vector2f position, sf::Vector2f size, sf::Color color, bool transparent)
	{
		this->pos = position;

		box.setSize(size);
		box.setOrigin(sf::Vector2f(box.getSize().x / 2, box.getSize().y / 2));
		box.setPosition(position);
		box.setFillColor(color);

		if (transparent)
		{
			box.setOutlineColor(sf::Color::White);
			box.setOutlineThickness(5);
		}
	}

	Box::~Box()
	{

	}

	void Box::update()
	{

	}

	void Box::draw(sf::RenderTarget & target)
	{
		target.draw(box);
	}

	//end




	//start
	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, const std::string buttonID, bool transparent)
	{
		this->buttonID = buttonID;
		this->pos = position;
		this->size = size;

		button.setSize(size);
		button.setOrigin(sf::Vector2f(button.getSize().x / 2, button.getSize().y / 2));
		button.setPosition(position);
		button.setFillColor(color);

		this->transparent = transparent;
		if (transparent)
		{
			button.setOutlineColor(sf::Color::White);
			button.setOutlineThickness(5);
		}

		buttonState = State::NONE;
	}

	Button::~Button()
	{

	}

	void Button::update(sf::RenderWindow &window)
	{
		checkMouseHovering(window);
		checkClicked(window);
		switch (buttonState)
		{
		case State::CLICKED:
			button.setOutlineThickness(-5);
			break;

		case State::HOVERING:
			button.setOutlineThickness(5);
			break;

		case State::NONE:
			button.setOutlineThickness(5);
			break;

		default:
			break;
		}
	}

	void Button::draw(sf::RenderTarget &target)
	{
		target.draw(button);
	}

	void Button::checkClicked(sf::RenderWindow &window)
	{
		auto mpos = sf::Mouse::getPosition(window);

		if (sf::Mouse::isButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
				&& button.getGlobalBounds().contains((float)mpos.x, (float)mpos.y)) //if the buttons contains the mousepos
				buttonState = State::CLICKED;
		}
	}

	void Button::checkMouseHovering(sf::RenderWindow &window)
	{
		auto mpos = sf::Mouse::getPosition(window);

		if (button.getGlobalBounds().contains((float)mpos.x, (float)mpos.y))
			buttonState = State::HOVERING;
		else
			buttonState = State::NONE;
	}

	//end



	//start
	Text::Text(sf::Vector2f position, sf::Color color, sf::Font &font, std::string text, unsigned int characterSize)
	{
		this->pos = position;
		this->size = size;
		this->txt = text;
		this->charSize = characterSize;

		this->text = sf::Text(text, font, characterSize);
		this->text.setPosition(pos);
	}

	Text::~Text()
	{
		
	}

	void Text::update()
	{

	}

	void Text::draw(sf::RenderTarget & target)
	{
		target.draw(text);
	}
	//end
}