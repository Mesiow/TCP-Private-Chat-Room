#include "ResourceManager.h"

sf::Font *ResourceManager::loadFont(const char * fileName)
{
	sf::Font *font = new sf::Font;
	if (!font->loadFromFile(fileName))
	{
		std::cout << "Font failed to load" << std::endl;
		delete font;
		return nullptr;
	}
	return font;
}