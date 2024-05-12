#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>

class StateManager;

struct MenuContext
{
    StateManager* stateManager;
    sf::Vector2f windowSize;
    sf::RectangleShape backgroundRect;
    sf::Shader backgroundShader;
    sf::Clock clock;
    sf::Font font;
    sf::Music menuMusic;
};

