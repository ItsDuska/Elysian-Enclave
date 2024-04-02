#pragma once

#include <SFML/System/Vector2.hpp>

namespace gui
{
	// From 0.0-1.0f to screen cordinates like 1080.
	sf::Vector2f windowToScreenCoordinates(const sf::Vector2u& windowSize, const sf::Vector2f& position);

	// From 0.0-1.0f to screen cordinates like 1080.
	sf::Vector2f windowToScreenCoordinates(const sf::Vector2f& windowSize, const sf::Vector2f& position);
}