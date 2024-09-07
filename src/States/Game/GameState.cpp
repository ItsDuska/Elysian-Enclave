#include "GameState.h"
#include <iostream>

GameWorldState::GameWorldState(StateManager* manager, sf::Vector2f& windowSize)
	:stateManager(manager), windowSize(windowSize),systems(entityManager,eventManager)
{
	const int TILE_SIZE = 12;

	EditorCreationInfo info{};
	info.spritePixelSize = { 16.f,16.f };
	info.tileSize = { windowSize.y / TILE_SIZE, windowSize.y / TILE_SIZE };
	info.animatedSpriteSheetTexturePath = "assets/sprites/blocks/Olli";
	info.layeredSpriteSheetTexturePath = "assets/sprites/blocks/Pietari.png";
	info.staticSpriteSheetTexturePath = "assets/sprites/blocks/Tuukka.png";
	info.objectSpriteSheetTexturePath = "assets/sprites/enTiTies/temp/Aku";

	this->handler = std::make_unique<TileWorldHandler>(info);
}

void GameWorldState::update(const float deltaTime)
{
	sf::Vector2f tempPos(0.f, 0.f);
	handler->update(tempPos);
}

void GameWorldState::render(sf::RenderTarget& window)
{
	handler->render(window, false);
}

void GameWorldState::wake()
{
}

void GameWorldState::handleEvent(sf::Event& event)
{
}
