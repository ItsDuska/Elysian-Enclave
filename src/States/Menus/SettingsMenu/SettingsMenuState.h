#pragma once
#include "States/Menus/MenuContext.h"
#include "States/State/State.h"
#include "SFML/Graphics.hpp"
#include "Gui/UiHandler/UserInterface.h"
#include "Gui/Buttons/Button.h"
#include "Core/Save/SaveManager.h"


struct GameSettings
{
	//float masterVolume;
	sf::Keyboard::Key forward;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key menu;
	//sf::Keyboard::Key jump;
	//sf::Keyboard::Key attack;
};

class SettingsMenuState : public State
{
public:
	SettingsMenuState(std::shared_ptr<MenuContext>& menuContext);

	void update(const float deltaTime) override;
	void render(sf::RenderTarget& window) override;
	void wake() override;
	void handleEvent(sf::Event& event) override;

private:
	std::shared_ptr<MenuContext> context;
	void exitFunction();

	gui::UserInterface ui;
	bool shouldExit;

	sf::Color renderAlpha;
	sf::RenderTexture renderTexture;
	float elapsedTime = 1.0f;

	SaveHandler save;

	GameSettings settings;
	
};