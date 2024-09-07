#include "MainMenuState.h"
#include "States/State/StateManager.h"
#include <iostream>
#include "Gui/GuiUtils.h"
#include "States/Menus/SettingsMenu/SettingsMenuState.h"
#include "Helpers/EasingMath.h"
#include "States/Menus/SavesMenu/SavesMenuState.h"
#include "States/Menus/WorldCreationMenu/WorldCreationMenuState.h"
#include "Resources/FontHandler.h"


// The real deal oh my my.... :clueless:
#include "States/Game/GameState.h"


static void testFunc()
{
    std::cout << "Hello form button!\n";
}

MainMenuState::MainMenuState(StateManager* manager, sf::Vector2f& windowSize)
    : context(std::make_shared<MenuContext>()),ui(4u)
{
    context->stateManager = manager;
    context->windowSize = windowSize;
    context->backgroundRect.setSize(windowSize);
    if (!context->menuMusic.openFromFile("assets\\audio\\music\\mainMenu\\The dawn.mp3"))
    {
        std::cout << "ERROR: Failed to open mainMenu music file.\n";
    }
    context->menuMusic.setLoop(true);
    context->menuMusic.setVolume(30.f);
    context->menuMusic.setPitch(0.72f);
    context->menuMusic.play();
    

    if (!context->backgroundShader.loadFromFile(
        "assets\\shaders\\StarShader.vert",
        "assets\\shaders\\StarShader.frag"))
    {
        std::cout << "Error loading MainMenu shaders!\n";
    }

    context->backgroundShader.setUniform("u_resolution", windowSize);
    initTextures();
    initButtons();

    renderTexture.create(context->windowSize.x, context->windowSize.y);
    renderAlpha = sf::Color(255, 255, 255, 0);
}

void MainMenuState::update(const float deltaTime)
{
    const float timePassed = context->clock.getElapsedTime().asSeconds();
    context->backgroundShader.setUniform("u_time", timePassed);

    elapsedTime += 0.01f;
    const float transparency = mUtils::easeInOutExpo(elapsedTime);
    renderAlpha = sf::Color(255, 255, 255, static_cast<sf::Uint8>(transparency * 255));

    ui.update();
}

void MainMenuState::render(sf::RenderTarget& window)
{
    if (!context)
    {
        std::cout << "menu_context is nullptr\n";
        return;
    }
    renderTexture.clear(sf::Color::Transparent);

    window.draw(context->backgroundRect, &context->backgroundShader);

    renderTexture.draw(magicCircle);
    ui.render(renderTexture);
    renderTexture.draw(logo);
    renderTexture.display();

    sf::Sprite renderWindow(renderTexture.getTexture());
    renderWindow.setColor(renderAlpha);
    window.draw(renderWindow);
}

void MainMenuState::wake()
{
    renderAlpha = sf::Color(255, 255, 255, 0);
    elapsedTime = 0.3f;
}

void MainMenuState::handleEvent(sf::Event& event)
{
}

void MainMenuState::initTextures()
{
    //Magic circle setup

    if (!magicCircleTexture.loadFromFile("assets\\sprites\\mainMenu\\magicCircle.png"))
    {
        std::cout << "Error loading MainMenu sprite: magic circle!\n";
    }

    magicCircleTexture.setSmooth(true);
    magicCircle.setTexture(magicCircleTexture);

    float scaleX = 0.5f * (context->windowSize.x / magicCircleTexture.getSize().x);
    float scaleY = 0.5f * (context->windowSize.y / magicCircleTexture.getSize().y);
    float scale = std::min(scaleX, scaleY);
    magicCircle.setScale(scale, scale);

    sf::Vector2f newSize(magicCircleTexture.getSize().x * scale, magicCircleTexture.getSize().y * scale);
    sf::Vector2f newPosition((context->windowSize.x - newSize.x) / 2, (context->windowSize.y - newSize.y) / 4);

    magicCircle.setPosition(newPosition);
}

void MainMenuState::initButtons()
{
    std::string filepath = "assets\\fonts\\yoster.ttf";

    Global::FontHandler::load();
    Global::FontHandler::addFont(filepath, Global::FontHandler::NORMAL_FONT);
    context->font = &Global::FontHandler::getFont(Global::FontHandler::NORMAL_FONT);
    
    const unsigned int NORMAL_FONT_SIZE = 50u;
    const float SCALE = std::min(context->windowSize.x, context->windowSize.y) / 800.0f;
    const unsigned int fontSize = static_cast<unsigned int>(NORMAL_FONT_SIZE * SCALE);
    sf::Color color(34u, 38u, 65u, 76u);

    StateManager* states = context->stateManager;



    std::string text;
    std::function<void()> function;

    if (SaveHandler::isDirectoryEmpty("world/progression"))
    {
        text.assign("Arise");
        //function = [this]() {context->stateManager->addState(std::make_unique<WorldCreationMenuState>(context), true); };


        context->menuMusic.~Music();
        // testiä varten menemme suoraan peliin
        function = [this]() {context->stateManager->addState(std::make_unique<GameWorldState>(context->stateManager,context->windowSize), true); };

    }
    else
    {
        context->menuMusic.~Music();
        text.assign("Continue");
        //function = [this]() {context->stateManager->addState(std::make_unique<GameState>(context), true); };
        //context->stateManager->addState(std::make_unique<GameState>(context,SaveManager::recentlyEditedDirectory("world")), true);
    }




    ui.addWidget(
        std::make_unique<Button>(
            sf::Vector2f{0.5f,0.68f},
            context->windowSize,
            color,
            fontSize,
            text,
            context->font,
            function
            // TODO: JATKA SIITÄ MAAILMASTA MITÄ VIIMEKSI ON PELATTU, JOS SITÄ EI OLE NIIN LUO UUSI MAAILMA
            //states->addState(GameState game(params...));}

        )
    );

    ui.addWidget(
        std::make_unique<Button>(
            sf::Vector2f{ 0.5f,0.75f},
            context->windowSize,
            color,
            fontSize,
            "Load Save",
            context->font,
            [this]() {
                context->stateManager->addState(std::make_unique<SavesMenuState>(context), false);
            }
        )
    );

    ui.addWidget(
        std::make_unique<Button>(
            sf::Vector2f{ 0.5f,0.83f },
            context->windowSize,
            color,
            fontSize,
            "Settings",
            context->font,
            [this]() {
                context->stateManager->addState(std::make_unique<SettingsMenuState>(context), false);
            }
        )
    );
   
    ui.addWidget(
        std::make_unique<Button>(
            sf::Vector2f{ 0.5f,0.91f },
            context->windowSize,
            color,
            fontSize,
            "Quit",
            context->font,
            [this]() {
                context->menuMusic.~Music();
                context->stateManager->exitCall();
            }
        )
    );
    
    logo.setString("Elysian Enclave");
    sf::Vector2f logoPosition = {};
    calculateLogoContext(logo, 100, logoPosition);
    logoPosition.y = 0;
    logo.setPosition(logoPosition);
}

void MainMenuState::calculateLogoContext(sf::Text& text, int originalFontSize, sf::Vector2f& position)
{
    text.setFont(*context->font);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(4);

    float scale = std::min(context->windowSize.x, context->windowSize.y) / 800.0f; // Olettaen alkuperäisen ikkunan koon 800x600

    // Asetetaan tekstin koko suhteessa alkuperäiseen kokoon.
    text.setCharacterSize(static_cast<unsigned int>(originalFontSize * scale));

    position.x = (context->windowSize.x - text.getLocalBounds().width) / 2;
    position.y = (context->windowSize.y - text.getLocalBounds().height) / 1.2f;
}
