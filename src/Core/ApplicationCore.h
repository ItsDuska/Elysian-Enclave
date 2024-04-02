#pragma once
#include <memory>
#include "States/State/StateManager.h"
#include <SFML/Graphics.hpp>

class AssetManager;

class ApplicationCore
{
public:
	ApplicationCore();
	~ApplicationCore();
	void run();
private:
	std::unique_ptr<sf::RenderWindow> window;
	StateManager states;
	sf::Event sfEvent;
	int currentState;
	sf::Clock deltaClock;
	AssetManager *assetManager;
private:
	void updateSFMLEvents();
	void update();
	void render();
};


