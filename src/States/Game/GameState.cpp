#include "GameState.h"
#include <iostream>
#include "Entities/BasicComponentData.h"
#include "Entities/player/PlayerInput.h"
#include "Entities/BasicRenderSystem.h"
#include "Entities/MovementSystem.h"
#include "Resources/TextureHandler.h"


GameWorldState::GameWorldState(StateManager* manager, sf::Vector2f& windowSize, sf::RenderWindow& window)
	:stateManager(manager), windowSize(windowSize),systems(entityManager,eventManager)
{
	std::string TEMP_PLAYER_SPRITE_PATH = "C:/Users/ollis/Pictures/tempGoofy/and_thats_a_fact.png";

	// setting texture manager...
	Global::TextureHandler::load();
	Global::TextureHandler::add(TEMP_PLAYER_SPRITE_PATH, "Player");

	const int TILE_SIZE = 12;

	EditorCreationInfo info{};
	info.spritePixelSize = { 16.f,16.f };
	info.tileSize = { windowSize.y / TILE_SIZE, windowSize.y / TILE_SIZE };
	info.animatedSpriteSheetTexturePath = "assets/sprites/blocks/Olli";
	info.layeredSpriteSheetTexturePath = "assets/sprites/blocks/Pietari.png";
	info.staticSpriteSheetTexturePath = "assets/sprites/blocks/Tuukka.png";
	info.objectSpriteSheetTexturePath = "assets/sprites/enTiTies/temp/Aku";

	this->handler = std::make_unique<TileWorldHandler>(info);

	playerID = entityManager.newEnity();

	EntityComponent::RigidBody* body = entityManager.addComponent<EntityComponent::RigidBody>(playerID);
	body->maxVelocity = 5.5f;
	body->acceleration = 1.05f;
	body->deceleration = 0.4f;
	EntityComponent::Transform* transform = entityManager.addComponent<EntityComponent::Transform>(playerID);
	transform->position = { 0,200 };
	EntityComponent::State* playerState = entityManager.addComponent<EntityComponent::State>(playerID);
	EntityComponent::Speed* speed= entityManager.addComponent<EntityComponent::Speed>(playerID);
	speed->speed = 0.55f;

	EntityComponent::Image* image = entityManager.addComponent<EntityComponent::Image>(playerID);
	image->sprite.setTexture(Global::TextureHandler::get("Player"));

	systems.add<MovementSystem>();
	systems.add<BasicRenderSystem>(&window);
	systems.wake();

}

GameWorldState::~GameWorldState()
{
	Global::TextureHandler::shutDown();
}

void GameWorldState::update(const float deltaTime)
{
	sf::Vector2f playerPosition = entityManager.getComponentPtr<EntityComponent::Transform>(playerID)->position;
	
	
	this->camera.setCenter(sf::Vector2f((int)playerPosition.x, playerPosition.y));

	handler->update(playerPosition);

	PlayerInput::updatePlayerInput(entityManager, deltaTime);
	systems.updateSystems(deltaTime);
}

void GameWorldState::render(sf::RenderTarget& window)
{
	window.setView(this->camera);
	handler->render(window, false);


	systems.lateUpdateSystems();
	//sf::Sprite& sprite = entityManager.getComponentPtr<EntityComponent::Image>(playerID)->sprite;
	//window.draw(sprite);
}

void GameWorldState::wake()
{
}

void GameWorldState::handleEvent(sf::Event& event)
{
}
