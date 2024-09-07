#pragma once
#include "Gui/Widget.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <functional>

class StateManager;

namespace guiButton
{
	//Base class. Do no use this as the actual button.
	class BaseButton
	{
	protected:
		void calculatePosition(sf::Vector2f& position, sf::Vector2f& windowSize);
		void setupCore(const sf::Color color,
			const unsigned int charSize,
			const std::string& buttonText,
			const sf::Font* font,
			std::function<void()> function
		);

		sf::Text text;
		sf::RectangleShape rect;
		std::function<void()> onActivation;
	};
}


// Regular button with click action.
class Button : public gui::Widget, public guiButton::BaseButton
{
public:
	Button(sf::Vector2f position,
		sf::Vector2f& windowSize,
		const sf::Color color,
		const unsigned int charSize,
		const std::string& buttonText,
		const sf::Font* font,
		std::function<void()> function
	);

	void render(sf::RenderTarget& window) const override final;
	bool update(gui::GuiEvent& event);
};

// Button with text box.
class TextButton : public gui::Widget, public guiButton::BaseButton
{
public:
	TextButton(sf::Vector2f position,
		sf::Vector2f& windowSize,
		const sf::Color color,
		const unsigned int charSize,
		const std::string& buttonText,
		const sf::Font* font,
		std::function<void()> function,
		const char* optionalDefaultAfterTextValue = nullptr
	);
	void render(sf::RenderTarget& window) const override final;
	bool update(gui::GuiEvent& event);

	void updateText(const char* newString);
private:
	std::string originalText;
	sf::Vector2f position;
	sf::Vector2f windowSize;
};





/*
class SettingsButton : public Button
{
public:
	SettingsButton(sf::Vector2f position,
		sf::Vector2f& windowSize,
		const sf::Color color,
		const unsigned int charSize,
		const std::string& buttonText,
		const sf::Font& font,
		std::function<void()> function
	);


private:
	bool isActive;
};

*/


/*
Slider button??
void handleEvent(sf::Event event) {
		if (event.type == sf::Event::MouseButtonPressed) {
			// Tarkista, onko hiiren klikkaus liukus‰‰timen alueella
			sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
			if (slider_.getGlobalBounds().contains(mousePosition)) {
				// P‰ivit‰ ‰‰nenvoimakkuus liukus‰‰timen sijainnin perusteella
				float relativePosition = mousePosition.x - position_.x;
				float maxPosition = slider_.getSize().x;
				volume_ = (relativePosition / maxPosition) * 100.0f;
				updateText();
				onVolumeChange_(volume_);
			}
		}
	}


*/