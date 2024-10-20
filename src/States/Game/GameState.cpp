#include "GameState.h"
#include <iostream>
#include "Entities/BasicComponentData.h"
#include "Entities/player/PlayerInput.h"
#include "Entities/BasicRenderSystem.h"
#include "Entities/MovementSystem.h"
#include "Resources/TextureHandler.h"
#include "Entities/AnimationSystem.h"
#include "Resources/loaders/EntitySpriteSheetAnimationLoader.h"


GameWorldState::GameWorldState(StateManager* manager, sf::Vector2f& windowSize, sf::RenderWindow& window)
	:stateManager(manager), windowSize(windowSize),systems(entityManager,eventManager)
{
	// setting texture manager...
	Global::TextureHandler::load();
	//Global::TextureHandler::add(TEMP_PLAYER_SPRITE_PATH, "Player");

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
	body->maxVelocity = 3.3f;
	body->acceleration = 1.04f;
	body->deceleration = 0.3f;
	EntityComponent::Transform* transform = entityManager.addComponent<EntityComponent::Transform>(playerID);
	transform->position = { 0,200 };
	EntityComponent::State* playerState = entityManager.addComponent<EntityComponent::State>(playerID);
	EntityComponent::Speed* speed= entityManager.addComponent<EntityComponent::Speed>(playerID);
	speed->speed = 0.4;

	EntityComponent::Image* image = entityManager.addComponent<EntityComponent::Image>(playerID);
	//image->sprite.setTexture(Global::TextureHandler::get("Player"));


	EntityComponent::Animation* animation = entityManager.addComponent<EntityComponent::Animation>(playerID);

	std::string TEMP_PLAYER_SPRITE_PATH = "assets/sprites/enTiTies/player/PlayerAnimations.png";
	std::filesystem::path guhPath = "assets/sprites/enTiTies/player/PlayerAnimations.png";
	loaders::loadAnimationFromSpriteSheet(entityManager, playerID, guhPath);
	//Global::TextureHandler::add(TEMP_PLAYER_SPRITE_PATH, "Player");

	
	animation->setAnimation(EntityComponent::Animation::AnimationArray::AnimationType::WALK_DOWN);

	systems.add<MovementSystem>();
	systems.add<AnimationSystem>();
	systems.add<BasicRenderSystem>(&window);
	systems.add<AnimationSystem>();
	systems.wake();

	camera.setSize(windowSize);
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
}

void GameWorldState::wake()
{
}

void GameWorldState::handleEvent(sf::Event& event)
{
}
