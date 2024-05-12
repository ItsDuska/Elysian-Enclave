#pragma once
#include "States/Menus/MenuContext.h"
#include "States/State/State.h"
#include "SFML/Graphics.hpp"
#include "Gui/UiHandler/UserInterface.h"
#include "Gui/Buttons/Button.h"
#include "Core/Save/SaveManager.h"


class SavesMenuState : public State
{
public:
	SavesMenuState(std::shared_ptr<MenuContext>& menuContext);

	void update(const float deltaTime) override;
	void render(sf::RenderTarget& window) override;
	void wake() override;
	void handleEvent(sf::Event& event) override;
private:
	void exitFunction();
private:
	std::shared_ptr<MenuContext> context;

	gui::UserInterface ui;
	bool shouldExit;
	bool deleteActivation;

	sf::Color renderAlpha;
	sf::RenderTexture renderTexture;
	float elapsedTime = 1.0f;

	SaveHandler save;
};

/*
TODO:
guh... emt tee t‰‰ helkutti loppuun senkin p‰lli. 
Kato obsidianista ne muistiinpanot.
*/