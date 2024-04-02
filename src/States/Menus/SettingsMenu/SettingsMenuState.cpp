#include "SettingsMenuState.h"
#include "States/State/StateManager.h"
#include <iostream>
#include "Gui/GuiUtils.h"
#include "Helpers/EasingMath.h"


SettingsMenuState::SettingsMenuState(std::shared_ptr<MenuContext>& menuContext)
    : context(menuContext),ui(10u), shouldExit(false), settings({})
{ 
    const unsigned int NORMAL_FONT_SIZE = 50u;
    const float SCALE = std::min(context->windowSize.x, context->windowSize.y) / 800.0f;

    const unsigned int fontSize = static_cast<unsigned int>(NORMAL_FONT_SIZE * SCALE);

    sf::Color color(34u, 38u, 65u, 76u);

    StateManager* states = context->stateManager;

    if (!save.confirmFile("data/settings/settings.data"))
    {
        std::cout << "ERROR: FILE IS SUS! Creating default values...\n";
        settings.forward = sf::Keyboard::W;
        settings.left = sf::Keyboard::A;
        settings.right = sf::Keyboard::D;
        settings.menu = sf::Keyboard::Escape;
    }
    else
    {
        save.read(reinterpret_cast<char*>(&settings), sizeof(GameSettings), SaveDataType::SETTINGS);
    }

    std::cout << "forward: " << settings.forward << "\n"
        << "left: " << settings.left << "\n"
        << "right: " << settings.right << "\n"
        << "menu: " << settings.menu << "\n";


    ui.addWidget(
    std::make_unique<TextButton>(
        sf::Vector2f{ 0.5f,0.23f },
        context->windowSize,
        color,
        fontSize,
        "up: ",
        context->font,
        [this]() {
            settings.forward = ui.getKey();
        },
        ui.sfKeyToChar(settings.forward))
    );
    
    ui.addWidget(
        std::make_unique<TextButton>(
            sf::Vector2f{ 0.5f,0.32f },
            context->windowSize,
            color,
            fontSize,
            "Left: ",
            context->font,
            [this]() {
                settings.left = ui.getKey();
            },
            ui.sfKeyToChar(settings.left)
        )
    );

    ui.addWidget(
        std::make_unique<TextButton>(
            sf::Vector2f{ 0.5f,0.40f },
            context->windowSize,
            color,
            fontSize,
            "right: ",
            context->font,
            [this]() {
                settings.right = ui.getKey();
            },
            ui.sfKeyToChar(settings.right)
        )
    );

    ui.addWidget(
        std::make_unique<TextButton>(
            sf::Vector2f{ 0.5f,0.50f },
            context->windowSize,
            color,
            fontSize,
            "Menu: ",
            context->font,
            [this]() {
                settings.menu = ui.getKey();
            },
            ui.sfKeyToChar(settings.menu)
        )
    );
    
    ui.addWidget(std::make_unique<Button>(
        sf::Vector2f{ 0.5f,0.7f },
        context->windowSize,
        color,
        fontSize,
        "Return",
        context->font,
        [this]() {
            //Save settings on here...
            save.write(reinterpret_cast<char*>(&settings), sizeof(GameSettings), SaveDataType::SETTINGS);
            shouldExit = true; }
    ));

    renderTexture.create(static_cast<unsigned int>(context->windowSize.x), static_cast<unsigned int>(context->windowSize.y));
    renderAlpha = sf::Color(255, 255, 255, 255);
}

void SettingsMenuState::update(const float deltaTime)
{
    const float timePassed = context->clock.getElapsedTime().asSeconds();
    context->backgroundShader.setUniform("u_time", timePassed);

    if (shouldExit)
    {
        exitFunction();
    }
    
    ui.update();
}

void SettingsMenuState::render(sf::RenderTarget& window)
{
    renderTexture.clear(sf::Color::Transparent);

    window.draw(context->backgroundRect, &context->backgroundShader);
    
    ui.render(renderTexture);
    renderTexture.display();

    sf::Sprite renderWindow(renderTexture.getTexture());
    renderWindow.setColor(renderAlpha);

    window.draw(renderWindow);
}

void SettingsMenuState::wake()
{
}

void SettingsMenuState::handleEvent(sf::Event& event)
{
    ui.handleEvent(event);
}

void SettingsMenuState::exitFunction()
{
    elapsedTime -= 0.025f;
    const float transparency = mUtils::easeInOutExpo(elapsedTime);
    renderAlpha = sf::Color(255, 255, 255, static_cast<sf::Uint8>(transparency * 255));

    if (elapsedTime <= 0.f)
    {
        context->stateManager->removeState();
    }
}
