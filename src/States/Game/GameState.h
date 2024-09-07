#pragma once
#include "States/State/State.h"
#include "States/State/StateManager.h"
#include "SFML/Graphics.hpp"


class GameWorldState : public State
{
public:
	GameWorldState(StateManager* manager, sf::Vector2f& windowSize);
	void update(const float deltaTime) override;
	void render(sf::RenderTarget& window) override;
	void wake() override;
	void handleEvent(sf::Event& event) override;

private:


private:
	sf::Vector2f windowSize;
	StateManager* stateManager;
};