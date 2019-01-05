#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class ResourceManager
{
public:
	static sf::Font *loadFont(const char *fileName);
};