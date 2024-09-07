#include "GameState.h"

GameWorldState::GameWorldState(StateManager* manager, sf::Vector2f& windowSize)
	:stateManager(manager), windowSize(windowSize)
{
}

void GameWorldState::update(const float deltaTime)
{
}

void GameWorldState::render(sf::RenderTarget& window)
{
}

void GameWorldState::wake()
{
}

void GameWorldState::handleEvent(sf::Event& event)
{
}
