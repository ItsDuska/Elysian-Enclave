#include "PlayerInput.h"
#include "Core/ECS/ECData/EntityManager.hpp"
#include "Entities/BasicComponentData.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


void PlayerInput::updatePlayerInput(EntityManager& entities, float dt)
{
	EntityComponent::RigidBody *rigidBody = entities.getComponentPtr<EntityComponent::RigidBody>(EntityComponent::PLAYER_ID);
	EntityComponent::Transform *transform = entities.getComponentPtr<EntityComponent::Transform>(EntityComponent::PLAYER_ID);
	EntityComponent::State* state = entities.getComponentPtr<EntityComponent::State>(EntityComponent::PLAYER_ID);
	EntityComponent::Speed* speed = entities.getComponentPtr<EntityComponent::Speed>(EntityComponent::PLAYER_ID);
	EntityComponent::Animation* animation = entities.getComponentPtr<EntityComponent::Animation>(EntityComponent::PLAYER_ID);

	bool keyPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		state->facing = EntityComponent::State::Direction::RIGHT;
		keyPressed = true;
		rigidBody->direction.x = speed->speed;
		state->possibleState = EntityComponent::EntityStates::WALKING;
		animation->setAnimation(EntityComponent::Animation::AnimationArray::AnimationType::WALK_RIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		state->facing = EntityComponent::State::Direction::LEFT;
		keyPressed = true;
		rigidBody->direction.x = -speed->speed;
		state->possibleState = EntityComponent::EntityStates::WALKING;
		animation->setAnimation(EntityComponent::Animation::AnimationArray::AnimationType::WALK_LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		state->facing = EntityComponent::State::Direction::UP;
		keyPressed = true;
		rigidBody->direction.y = -speed->speed;
		state->possibleState = EntityComponent::EntityStates::WALKING;
		animation->setAnimation(EntityComponent::Animation::AnimationArray::AnimationType::WALK_UP);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		state->facing = EntityComponent::State::Direction::DOWN;
		keyPressed = true;
		rigidBody->direction.y = speed->speed;
		state->possibleState = EntityComponent::EntityStates::WALKING;
		animation->setAnimation(EntityComponent::Animation::AnimationArray::AnimationType::WALK_DOWN);
	}

	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		keyPressed = true;
		rigidBody->direction = { 0,0 };
		state->possibleState = EntityComponent::EntityStates::ATTACK;
	}

	else if (!keyPressed)
	{
		rigidBody->direction.x = 0;
		rigidBody->direction.y = 0;
		state->possibleState = EntityComponent::EntityStates::IDLE;
		animation->setAnimation(EntityComponent::Animation::AnimationArray::AnimationType::WALK_BACKWARDS_FACING_DOWN);
	}
}
