#pragma once
#include "States/Menus/MenuContext.h"
#include "States/State/State.h"
#include "SFML/Graphics.hpp"
#include "Gui/UiHandler/UserInterface.h"


class StateManager;

class MainMenuState : public State
{
public:
    MainMenuState(StateManager* manager, sf::Vector2f& windowSize,sf::RenderWindow& window);

    void update(const float deltaTime) override;
    void render(sf::RenderTarget& window) override;
    void wake() override;
    void handleEvent(sf::Event& event) override;
private: 
    void initTextures();
    void initButtons(sf::RenderWindow& window);
    void calculateLogoContext(sf::Text& text, int originalFontSize, sf::Vector2f& position);
private:
    std::shared_ptr<MenuContext> context;
    float elapsedTime = 0.0f;

    //magic circle
    sf::Texture magicCircleTexture;
    sf::Sprite magicCircle;
    sf::Text logo;

    gui::UserInterface ui;
    
    sf::Color renderAlpha;
    sf::RenderTexture renderTexture;
};