#include "GuiUtils.h"

sf::Vector2f gui::windowToScreenCoordinates(const sf::Vector2u& windowSize, const sf::Vector2f& position)
{
	return sf::Vector2f(windowSize.x * position.x, windowSize.y * position.y);
}

sf::Vector2f gui::windowToScreenCoordinates(const sf::Vector2f& windowSize, const sf::Vector2f& position)
{
	return sf::Vector2f(windowSize.x * position.x, windowSize.y * position.y);
}

