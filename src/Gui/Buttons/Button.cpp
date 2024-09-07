#include "Button.h"
#include "Gui/GuiUtils.h"


void guiButton::BaseButton::calculatePosition(sf::Vector2f& position, sf::Vector2f& windowSize)
{
	sf::FloatRect textBounds = text.getLocalBounds();
	sf::Vector2f fixedboundsSize = textBounds.getSize() * 1.25f;

	sf::Vector2f fixedPosition(
		(windowSize.x - fixedboundsSize.x) * position.x,
		(windowSize.y - fixedboundsSize.y) * position.y
	);

	rect.setPosition(fixedPosition);
	rect.setSize(fixedboundsSize);

	text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	text.setPosition(fixedPosition + rect.getSize() / 2.0f);
}

void guiButton::BaseButton::setupCore(const sf::Color color,
	const unsigned int charSize,
	const std::string& buttonText,
	const sf::Font* font,
	std::function<void()> function
)
{
	text.setFont(*font);
	text.setString(buttonText);
	text.setCharacterSize(charSize);
	text.setFillColor(sf::Color::White);

	rect.setFillColor(color);

	onActivation = function;
}

Button::Button(sf::Vector2f position,
	sf::Vector2f& windowSize,
	const sf::Color color,
	const unsigned int charSize,
	const std::string& buttonText,
	const sf::Font* font,
	std::function<void()> function)
{
	this->onActivation = function;

	setupCore(color, charSize, buttonText, font, function);
	calculatePosition(position, windowSize);
}

void Button::render(sf::RenderTarget& window) const
{
	window.draw(rect);
	window.draw(text);
}

bool Button::update(gui::GuiEvent& event)
{
	if (!this->rect.getGlobalBounds().contains(event.mousePosition))
	{
		text.setFillColor(sf::Color::White);
		return false;
	}

	text.setFillColor(sf::Color::Cyan);

	if (event.mousePressed)
	{
		onActivation();
		event.mousePressed = false;
		return true;
	}

	return false;
}


TextButton::TextButton(sf::Vector2f position,
	sf::Vector2f& windowSize,
	const sf::Color color,
	const unsigned int charSize,
	const std::string& buttonText,
	const sf::Font* font,
	std::function<void()> function,
	const char* optionalDefaultAfterTextValue
)
	: position(position),windowSize(windowSize)
{
	originalText = buttonText;
	

	if (optionalDefaultAfterTextValue)
	{
		setupCore(color, charSize, buttonText + optionalDefaultAfterTextValue, font, function);
	}
	else
	{
		setupCore(color, charSize, buttonText, font, function);
	}
	
	calculatePosition(position, windowSize);
}

void TextButton::render(sf::RenderTarget& window) const
{
	window.draw(rect);
	window.draw(text);
}

bool TextButton::update(gui::GuiEvent& event)
{
	if (!this->rect.getGlobalBounds().contains(event.mousePosition))
	{
		text.setFillColor(sf::Color::White);
		return false;
	}

	if (!event.mousePressed)
	{
		text.setFillColor(sf::Color::Cyan);
		return false;
	}

	text.setFillColor(sf::Color::Green);
	
	if (!event.keyPressed)
	{
		return true;
	}

	updateText(event.textInput);
	event.mousePressed = false;
	event.keyPressed = false;

	return true;
}

void TextButton::updateText(const char* newString)
{
	if (!newString)
	{
		return;
	}

	text.setString(originalText + newString);
	calculatePosition(position, windowSize);

	if (onActivation)
	{
		onActivation();
	}
}

