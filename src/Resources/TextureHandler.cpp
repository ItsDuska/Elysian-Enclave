#include "TextureHandler.h"
#include <iostream>
#include <cassert>

static Global::TextureHandler* instance = nullptr;

void Global::TextureHandler::load()
{
	assert(!instance);
	instance = new TextureHandler();
}

void Global::TextureHandler::shutDown()
{
	assert(instance);

	delete instance;
	instance = nullptr;
}

void Global::TextureHandler::add(std::string& filepath, std::string name)
{
	assert(instance);
	instance->addTexctureFromInstance(filepath,name);
}


sf::Texture& Global::TextureHandler::get(std::string name)
{
	assert(instance);
	return instance->getTexctureFromInstance(name);
}

sf::Texture& Global::TextureHandler::get(std::string& name)
{
	assert(instance);
	return instance->getTexctureFromInstance(name);
}

Global::TextureHandler::TextureHandler()
{
}


Global::TextureHandler::~TextureHandler()
{
}

void Global::TextureHandler::addTexctureFromInstance(std::string& filepath, std::string& name)
{
	sf::Texture texture;

	if (!texture.loadFromFile(filepath))
	{
		std::cerr << "Failed to load texture: " << name << " with the following filepath:\n" << filepath << "\n";
		return;
	}
	
	textures.emplace(name, std::move(texture));
}

sf::Texture& Global::TextureHandler::getTexctureFromInstance(std::string& name)
{
	return textures.at(name);
}
