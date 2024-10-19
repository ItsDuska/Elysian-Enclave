#include "ApplicationCore.h"
#include "States/Menus/MainMenu/MainMenuState.h"
#include <iostream>

//#define MEASURE

#ifdef MEASURE
#include <chrono>
#endif 



ApplicationCore::ApplicationCore()
{
	sf::VideoMode currentMode = sf::VideoMode::getDesktopMode();
	//sf::VideoMode currentMode = sf::VideoMode::getFullscreenModes()[0];
	window = std::make_unique<sf::RenderWindow>(currentMode, "Elysian Enclave", sf::Style::Fullscreen);
	window->setFramerateLimit(60u); // 60 default

	sf::Vector2u uWindowSize = window->getSize();
	sf::Vector2f windowSize(static_cast<float>(uWindowSize.x), static_cast<float>(uWindowSize.y));
	states.addState(std::make_unique<MainMenuState>(&states, windowSize,*window), false);
}

ApplicationCore::~ApplicationCore()
{
}

void ApplicationCore::run()
{
	while (window->isOpen() && states.isActive())
	{
#ifdef MEASURE
		auto t1 = std::chrono::high_resolution_clock::now();
#endif

		states.processChanges();
		update();
		render();

#ifdef MEASURE
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms_double = t2 - t1;
		std::cout << ms_double.count() << "ms\n";
#endif
	}
}

void ApplicationCore::updateSFMLEvents()
{
	while (window->pollEvent(sfEvent)) {
		switch (sfEvent.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			//resize funtcion here
			break;
		case sf::Event::KeyPressed:
			if (sfEvent.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
			break;
		//case sf::Event::TextEntered:
			//states.currentState()->handleEvent(sfEvent);
		default:
			break;
		}
		states.currentState()->handleEvent(sfEvent);
	}
}

void ApplicationCore::update()
{
	const float deltaTime = deltaClock.restart().asSeconds();
	updateSFMLEvents();
	states.currentState()->update(deltaTime);
}

void ApplicationCore::render()
{
	window->clear(sf::Color::Black);
	states.currentState()->render(*window);
	window->display();
}
