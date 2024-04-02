#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include "Gui/Widget.h"
#include <SFML/Graphics.hpp>


namespace gui
{
	class UserInterface
	{
	public:
		UserInterface(const uint32_t maxWidgets);
		
		void addWidget(std::unique_ptr<Widget> element);

		void update();
		void render(sf::RenderTarget& target);
		void handleEvent(sf::Event& event);
		const sf::Keyboard::Key getKey() const;
		const char* sfKeyToChar(sf::Keyboard::Key key);
	private:
		GuiEvent eventInfo;
		bool active;
		unsigned int currentIndex;
		std::vector<std::unique_ptr<Widget>> widgets;

		const std::unordered_map<sf::Keyboard::Key, const char*> keyNames;

		sf::Clock clock;
	};

}

