#include "SavesMenuState.h"
#include "Helpers/EasingMath.h"
#include "States/State/StateManager.h"

SavesMenuState::SavesMenuState(std::shared_ptr<MenuContext>& menuContext)
	:context(menuContext), ui(6u), shouldExit(false),deleteActivation(false)
{
    const unsigned int NORMAL_FONT_SIZE = 50u;
    const float SCALE = std::min(context->windowSize.x, context->windowSize.y) / 800.0f;
    const unsigned int fontSize = static_cast<unsigned int>(NORMAL_FONT_SIZE * SCALE);
    sf::Color color(34u, 38u, 65u, 76u);

    StateManager* states = context->stateManager;

    ui.addWidget(
        std::make_unique<Button>(
            sf::Vector2f{ 0.1f,0.6f },
            context->windowSize,
            color,
            fontSize,
            "Return",
            context->font,
            [this]() {
                shouldExit = true;
            }
        )
    );


    ui.addWidget(
        std::make_unique<Button>(
            sf::Vector2f{ 0.1f,0.4f },
            context->windowSize,
            color,
            fontSize,
            "Create New World",
            context->font,
            []() {
                /*
                Siirry uuteen Stateen...
                poista kaikki vanhat statet samalla. Tähän uus funktio state managerriin


                */
            }
        )
    );

    //TODO MUUTA TÄÄ CHECK MARK BUTTONIKS / WIDGETIKSI
    ui.addWidget(
        std::make_unique<Button>(
            sf::Vector2f{ 0.1f,0.5f },
            context->windowSize,
            color,
            fontSize,
            "Delete World",
            context->font,
            [this]() {
                deleteActivation = !deleteActivation;
            }
        )
    );

    renderTexture.create(static_cast<unsigned int>(context->windowSize.x), static_cast<unsigned int>(context->windowSize.y));
    renderAlpha = sf::Color(255, 255, 255, 255);

}

void SavesMenuState::update(const float deltaTime)
{
    const float timePassed = context->clock.getElapsedTime().asSeconds();
    context->backgroundShader.setUniform("u_time", timePassed);

    if (shouldExit)
    {
        exitFunction();
    }

    ui.update();
}

void SavesMenuState::render(sf::RenderTarget& window)
{
    renderTexture.clear(sf::Color::Transparent);

    window.draw(context->backgroundRect, &context->backgroundShader);

    ui.render(renderTexture);
    renderTexture.display();

    sf::Sprite renderWindow(renderTexture.getTexture());
    renderWindow.setColor(renderAlpha);

    window.draw(renderWindow);
}

void SavesMenuState::wake()
{
    //guh...
}

void SavesMenuState::handleEvent(sf::Event& event)
{
    ui.handleEvent(event);
}

void SavesMenuState::exitFunction()
{
    elapsedTime -= 0.025f;
    const float transparency = mUtils::easeInOutExpo(elapsedTime);
    renderAlpha = sf::Color(255, 255, 255, static_cast<sf::Uint8>(transparency * 255));

    if (elapsedTime <= 0.f)
    {
        context->stateManager->removeState();
    }
}
