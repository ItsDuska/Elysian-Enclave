#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>


namespace gui
{
	struct GuiEvent
	{
		bool mousePressed;
		sf::Vector2f mousePosition;
		bool keyPressed;
		
		sf::Keyboard::Key key;
		const char* textInput;
	};
	
	class Widget
	{
	public:
		virtual bool update(GuiEvent& event) = 0;
		virtual void render(sf::RenderTarget& target) const = 0;
	};
}

