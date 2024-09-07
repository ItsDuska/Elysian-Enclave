#include "FontHandler.h"
#include <iostream>
#include <cassert>


static Global::FontHandler* instance = nullptr;

void Global::FontHandler::load()
{
	assert(!instance);
	instance = new FontHandler();

}

void Global::FontHandler::shutDown()
{
	assert(instance);

	delete instance;
	instance = nullptr;
}

void Global::FontHandler::addFont(std::string& filepath, FontType type)
{
	assert(instance);
	instance->addFontFromInstance(filepath, type);
}

sf::Font& Global::FontHandler::getFont(FontType type)
{
	assert(instance);
	return instance->getFontFromInstance(type);
}

Global::FontHandler::FontHandler()
{

}

Global::FontHandler::~FontHandler()
{
}

void Global::FontHandler::addFontFromInstance(std::string& filepath, FontType type)
{
	if (!fonts[type].loadFromFile(filepath))
	{
		std::cerr << "Error loading font: " + filepath + "\n";
	}
}

sf::Font& Global::FontHandler::getFontFromInstance(FontType type)
{
	return fonts[type];
}
